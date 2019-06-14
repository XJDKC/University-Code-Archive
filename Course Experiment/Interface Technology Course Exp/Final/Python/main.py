import random
import sys
from time import sleep
import serial
import threading

from PySide2.QtCore import QTimer, SIGNAL, QObject, QEvent
from PySide2.QtGui import QPainter, QColor, QPen, QCloseEvent
from PySide2.QtWidgets import QMainWindow, QApplication, QWidget, QLabel

from ui_mainwindow import Ui_MainWindow


class MainWindow(QMainWindow):
    tempList = []
    curTemp = 0
    curPower = 0
    curGear = 0
    curDoorWindowState = 0

    run = True
    timer = QTimer()
    ser = serial.Serial()

    def __init__(self):
        QMainWindow.__init__(self)

        self.ser.port = sys.argv[1]
        self.ser.baudrate = 115200
        self.ser.timeout = 0.5
        self.ser.write_timeout = 0.5
        self.ser.open()
        if not self.ser.is_open:
            sys.exit(-1)

        self.setWindowTitle("Interface Technology")
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.curve.installEventFilter(self)

        self.timer.start(1000)
        self.connect(self.timer, SIGNAL("timeout()"), self.refresh)
        self.connect(self.timer, SIGNAL("timeout()"), self.update)

        self.ui.setTemp.valueChanged.connect(self.onSetTempChanged)
        self.ui.setWind.valueChanged.connect(self.onSetWindChanged)

        self.ui.checkBox_1.clicked.connect(self.onCheckBoxClicked)
        self.ui.checkBox_2.clicked.connect(self.onCheckBoxClicked)
        self.ui.checkBox_3.clicked.connect(self.onCheckBoxClicked)
        self.ui.checkBox_4.clicked.connect(self.onCheckBoxClicked)
        self.ui.checkBox_5.clicked.connect(self.onCheckBoxClicked)
        self.ui.checkBox_6.clicked.connect(self.onCheckBoxClicked)

        self.tempList = [0 for n in range(0, 61)]

        self.ui.power.setText('%.2f W'%self.curPower)
        self.ui.gear.setText('%d D'%self.curGear)
        #self.send(b'P%d\n' % self.curPower)
        #self.send(b'L%d\n' % self.curGear)

        thread = threading.Thread(target=self.recv, args=[])
        thread.start()


    def onSetTempChanged(self, value_as_double):
        oldPower = self.curPower
        if self.curTemp > value_as_double:
            self.curPower = 0
        elif self.curTemp < value_as_double:
            div = value_as_double - self.curTemp
            self.curPower = min(int(div/0.5), 9)
        self.ui.power.setText('%.2f W' % self.curPower)
        if oldPower != self.curPower:
            print("SendPower")
            print(b'P%d\n' % self.curPower)
            self.send(b'P%d\n' % self.curPower)


    def onSetWindChanged(self, value_as_int):
        oldGear = self.curGear
        self.curGear = max(value_as_int-self.updateDoorWindowState(), 0)
        self.ui.gear.setText('%d D' % self.curGear)
        if oldGear != self.curGear:
            print("SendWind")
            print(b'L%d\n' % self.curGear)
            self.send(b'L%d\n' % self.curGear)

    def eventFilter(self, watched: QObject, event: QEvent) -> bool:
        if watched == self.ui.curve and event.type() == QEvent.Paint:
            self.drawCurve()

        return QWidget.eventFilter(self, watched, event)

    def refresh(self):
        self.tempList.append(self.curTemp)
        if (len(self.tempList) > 61):
            self.tempList.pop(0)

    def send(self, data):
        for item in data:
            self.ser.write(item)
            print('Send:' + str(item))
            sleep(0.2)

    def recv(self):
        while self.run:
            command = self.ser.readline()
            if len(command):
                if command.startswith(b'T'):
                    self.curTemp = float(command.decode('ascii')[1:-1])
                    self.ui.setTemp.emit(SIGNAL('valueChanged'), self.ui.setTemp.value())
                    # self.onSetTempChanged(self.ui.setTemp.value())
                elif command.startswith(b'S'):
                    self.curDoorWindowState = int(command.decode('ascii')[1:-1])
                    self.ui.setWind.emit(SIGNAL('valueChanged'), self.ui.setWind.value())
                    # self.onSetWindChanged(self.ui.setWind.value())
                print("Debug:" + command.decode())
                #else:
                #    print("Debug:"+command.decode())

    def updateDoorWindowState(self):
        self.ui.checkBox_1.setChecked(self.curDoorWindowState & 0x1)
        self.ui.checkBox_2.setChecked(self.curDoorWindowState & 0x2)
        self.ui.checkBox_3.setChecked(self.curDoorWindowState & 0x4)
        self.ui.checkBox_4.setChecked(self.curDoorWindowState & 0x8)
        self.ui.checkBox_5.setChecked(self.curDoorWindowState & 0x10)
        self.ui.checkBox_6.setChecked(self.curDoorWindowState & 0x20)
        rtn = 0
        temp = self.curDoorWindowState
        for i in range(0, 5):
            if temp & 0x1:
                if i <= 1:
                    rtn += 2
                else:
                    rtn += 1
            temp = temp >> 1
        return rtn

    def onCheckBoxClicked(self):
        self.updateDoorWindowState()

    def drawCurve(self):
        painter = QPainter(self.ui.curve)
        painter.setPen(QColor(114, 159, 207))

        width = self.ui.curve.width()
        height = self.ui.curve.height()

        for i in range(0, height,25):
            painter.drawLine(0, i, width, i)

        for i in range(0, width,20):
            painter.drawLine(i, 0, i, height)

        pen = QPen()
        pen.setColor(QColor(114, 159, 207))
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setRenderHint(QPainter.Antialiasing, True)
        maxTemp = max(self.tempList)
        minTemp = min(self.tempList)
        stepTemp = max((maxTemp-minTemp)/10, 0.01)
        midTemp = (maxTemp + minTemp) / 2.0
        fromTemp = (midTemp - stepTemp * 5.5)
        toTemp = (midTemp + stepTemp * 5.5)
        gapTemp = 11 * stepTemp
        for i in range(0, 60):
            painter.drawLine(i*width/60.0,height*((toTemp - self.tempList[i])/gapTemp),(i+1)*width/60.0, height*((toTemp - self.tempList[i+1])/gapTemp))
        temp = toTemp
        self.ui.tempLabel_1.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_2.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_3.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_4.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_5.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_6.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_7.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_8.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_9.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_10.setText("%.2f" % temp); temp -= stepTemp
        self.ui.tempLabel_11.setText("%.2f" % temp)

        # for i in range(1,11):
        #     print("tempLabel_%d" % i)
        #     qlabel = self.findChild(QLabel, ("tempLabel_%d" % i))
        #     print(qlabel)
        #     print(temp)
        #     qlabel.setText("%.2f"%temp)
        #     temp -= stepTemp

    def closeEvent(self, event:QCloseEvent):
        self.run = False

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print('Please input the argument!')
        sys.exit(-1)

    print(sys.argv)
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
