package Model;

import java.sql.Timestamp;
import java.util.Date;

public class Register {
    private String registerNo;
    private String typeNo;
    private String doctorNo;
    private String patientNo;
    private int currentNum;
    private boolean unregister;
    private double realCost;
    private Timestamp registerDate;
    private Timestamp treatDate;

    public Register() {}

    public Register(String registerNo, String typeNo, String doctorNo, String patientNo, int currentNum, boolean unregister, double realCost, Timestamp rigisterDate, Timestamp treatDate) {
        this.registerNo = registerNo;
        this.typeNo = typeNo;
        this.doctorNo = doctorNo;
        this.patientNo = patientNo;
        this.currentNum = currentNum;
        this.unregister = unregister;
        this.realCost = realCost;
        this.registerDate = rigisterDate;
        this.treatDate = treatDate;
    }

    public String getRegisterNo() {
        return registerNo;
    }

    public void setRegisterNo(String registerNo) {
        this.registerNo = registerNo;
    }

    public String getTypeNo() {
        return typeNo;
    }

    public void setTypeNo(String typeNo) {
        this.typeNo = typeNo;
    }

    public String getDoctorNo() {
        return doctorNo;
    }

    public void setDoctorNo(String doctorNo) {
        this.doctorNo = doctorNo;
    }

    public String getPatientNo() {
        return patientNo;
    }

    public void setPatientNo(String patientNo) {
        this.patientNo = patientNo;
    }

    public int getCurrentNum() {
        return currentNum;
    }

    public void setCurrentNum(int currentNum) {
        this.currentNum = currentNum;
    }

    public boolean isUnregister() {
        return unregister;
    }

    public void setUnregister(boolean unregister) {
        this.unregister = unregister;
    }

    public double getRealCost() {
        return realCost;
    }

    public void setRealCost(double realCost) {
        this.realCost = realCost;
    }

    public Timestamp getRegisterDate() {
        return registerDate;
    }

    public void setRegisterDate(Timestamp registerDate) {
        this.registerDate = registerDate;
    }

    public Timestamp getTreatDate() {
        return treatDate;
    }

    public void setTreatDate(Timestamp treatDate) {
        this.treatDate = treatDate;
    }
}
