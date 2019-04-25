package Model;

import java.util.Date;

public class Register {
    private String registerNo;
    private String typeNo;
    private String doctorNo;
    private String patientNo;
    private String currentNum;
    private boolean unregister;
    private double realCost;
    private Date rigisterDate;
    private Date treatDate;

    public Register() {}

    public Register(String registerNo, String typeNo, String doctorNo, String patientNo, String currentNum, boolean unregister, double realCost, Date rigisterDate, Date treatDate) {
        this.registerNo = registerNo;
        this.typeNo = typeNo;
        this.doctorNo = doctorNo;
        this.patientNo = patientNo;
        this.currentNum = currentNum;
        this.unregister = unregister;
        this.realCost = realCost;
        this.rigisterDate = rigisterDate;
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

    public String getCurrentNum() {
        return currentNum;
    }

    public void setCurrentNum(String currentNum) {
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

    public Date getRigisterDate() {
        return rigisterDate;
    }

    public void setRigisterDate(Date rigisterDate) {
        this.rigisterDate = rigisterDate;
    }

    public Date getTreatDate() {
        return treatDate;
    }

    public void setTreatDate(Date treatDate) {
        this.treatDate = treatDate;
    }


}
