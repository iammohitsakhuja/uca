import java.util.Scanner;

class CountPalindrome {
  static boolean isPalindrome(String str) {
    StringBuilder s = new StringBuilder(str);

    return s.reverse().toString().equals(str);
  }

  static int countPalindrome(String str) {
    String[] tokens = str.split("\\s");

    int count = 0;
    for (String token : tokens) if (isPalindrome(token)) count++;

    return count;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    String str = scanner.nextLine();
    System.out.println("Count of palindrome words: " + countPalindrome(str));
  }
}
