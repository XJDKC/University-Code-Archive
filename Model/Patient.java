package Model;

import java.util.Date;

public class Patient {
    private String patientNo;
    private String patientName;
    private String password;
    private double balance;
    private Date lastVisit;

    public Patient() {
    }

    public Patient(String patientNo, String patientName, String password, double balance, Date lastVisit) {
        this.patientNo = patientNo;
        this.patientName = patientName;
        this.password = password;
        this.balance = balance;
        this.lastVisit = lastVisit;
    }

    public String getPatientNo() {
        return patientNo;
    }

    public void setPatientNo(String patientNo) {
        this.patientNo = patientNo;
    }

    public String getPatientName() {
        return patientName;
    }

    public void setPatientName(String patientName) {
        this.patientName = patientName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public double getBalance() {
        return balance;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    }

    public Date getLastVisit() {
        return lastVisit;
    }

    public void setLastVisit(Date lastVisit) {
        this.lastVisit = lastVisit;
    }
}
