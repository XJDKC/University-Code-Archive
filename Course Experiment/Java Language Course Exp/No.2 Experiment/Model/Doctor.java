package Model;

import java.util.Date;

public class Doctor {
    private String doctorNo;
    private String deptBelong;
    private String doctorName;
    private String nameAbbr;
    private String password;
    private boolean isExpert;
    private Date lastVisit;

    public Doctor() {
    }

    public Doctor(String doctorNo, String deptBelong, String doctorName, String nameAbbr, String password, boolean isExpert, Date lastVisit) {
        this.doctorNo = doctorNo;
        this.deptBelong = deptBelong;
        this.doctorName = doctorName;
        this.nameAbbr = nameAbbr;
        this.password = password;
        this.isExpert = isExpert;
        this.lastVisit = lastVisit;
    }

    public String getDoctorNo() {
        return doctorNo;
    }

    public void setDoctorNo(String doctorNo) {
        this.doctorNo = doctorNo;
    }

    public String getDeptBelong() {
        return deptBelong;
    }

    public void setDeptBelong(String deptBelong) {
        this.deptBelong = deptBelong;
    }

    public String getDoctorName() {
        return doctorName;
    }

    public void setDoctorName(String doctorName) {
        this.doctorName = doctorName;
    }

    public String getNameAbbr() {
        return nameAbbr;
    }

    public void setNameAbbr(String nameAbbr) {
        this.nameAbbr = nameAbbr;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public boolean isExpert() {
        return isExpert;
    }

    public void setExpert(boolean expert) {
        isExpert = expert;
    }

    public Date getLastVisit() {
        return lastVisit;
    }

    public void setLastVisit(Date lastVisit) {
        this.lastVisit = lastVisit;
    }
}
