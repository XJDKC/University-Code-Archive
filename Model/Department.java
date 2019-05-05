package Model;

public class Department {
    private String deptNo;
    private String deptName;
    private String nameAbbr;

    public Department() {
    }

    public Department(String deptNo, String deptName, String nameAbbr) {
        this.deptNo = deptNo;
        this.deptName = deptName;
        this.nameAbbr = nameAbbr;
    }

    public String getDeptNo() {
        return deptNo;
    }

    public void setDeptNo(String deptNo) {
        this.deptNo = deptNo;
    }

    public String getDeptName() {
        return deptName;
    }

    public void setDeptName(String deptName) {
        this.deptName = deptName;
    }

    public String getNameAbbr() {
        return nameAbbr;
    }

    public void setNameAbbr(String nameAbbr) {
        this.nameAbbr = nameAbbr;
    }
}
