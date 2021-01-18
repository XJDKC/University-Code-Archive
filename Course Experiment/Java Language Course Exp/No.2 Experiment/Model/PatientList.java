package Model;

import java.sql.Timestamp;

public class PatientList {
    String registerNo;
    String patientName;
    Timestamp registerDate;
    String registerType;

    public PatientList() {
    }

    public PatientList(String registerNo, String patientName, Timestamp registerDate, String registerType) {
        this.registerNo = registerNo;
        this.patientName = patientName;
        this.registerDate = registerDate;
        this.registerType = registerType;
    }

    public String getRegisterNo() {
        return registerNo;
    }

    public void setRegisterNo(String registerNo) {
        this.registerNo = registerNo;
    }

    public String getPatientName() {
        return patientName;
    }

    public void setPatientName(String patientName) {
        this.patientName = patientName;
    }

    public Timestamp getRegisterDate() {
        return registerDate;
    }

    public void setRegisterDate(Timestamp registerDate) {
        this.registerDate = registerDate;
    }

    public String getRegisterType() {
        return registerType;
    }

    public void setRegisterType(String registerType) {
        this.registerType = registerType;
    }
}
