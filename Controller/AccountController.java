package Controller;

public class AccountController {

    private static String accountName;
    private static boolean accountType;

    public static String getAccountName() {
        return accountName;
    }

    public static void setAccountName(String accountName) {
        AccountController.accountName = accountName;
    }

    public static boolean isAccountType() {
        return accountType;
    }

    public static void setAccountType(boolean accountType) {
        AccountController.accountType = accountType;
    }
}
