package Model;

public class IncomeList {
    private String deptName;
    private String doctorNo;
    private String doctorName;
    private String registerType;
    private int registerNum;
    private double totalIncome;

    public IncomeList() {
    }

    public IncomeList(String deptName, String doctorNo, String doctorName, String registerType, int registerNum, double totalIncome) {
        this.deptName = deptName;
        this.doctorNo = doctorNo;
        this.doctorName = doctorName;
        this.registerType = registerType;
        this.registerNum = registerNum;
        this.totalIncome = totalIncome;
    }

    public String getDeptName() {
        return deptName;
    }

    public void setDeptName(String deptName) {
        this.deptName = deptName;
    }

    public String getDoctorNo() {
        return doctorNo;
    }

    public void setDoctorNo(String doctorNo) {
        this.doctorNo = doctorNo;
    }

    public String getDoctorName() {
        return doctorName;
    }

    public void setDoctorName(String doctorName) {
        this.doctorName = doctorName;
    }

    public String getRegisterType() {
        return registerType;
    }

    public void setRegisterType(String registerType) {
        this.registerType = registerType;
    }

    public int getRegisterNum() {
        return registerNum;
    }

    public void setRegisterNum(int registerNum) {
        this.registerNum = registerNum;
    }

    public double getTotalIncome() {
        return totalIncome;
    }

    public void setTotalIncome(double totalIncome) {
        this.totalIncome = totalIncome;
    }
}
