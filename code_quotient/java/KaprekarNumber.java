/**
 * Write a program to find the given number is kaprekar or not. A number if kaprekar if the
 * representation of its square can be split into two parts that add up to the original number. For
 * instance, 45 is a Kaprekar number, because 45^2 = 2025 and 20 + 25 = 45. Whereas 13 is not as
 * 13^2 = 169 which can be split in two ways (1+69) and (16+9), but any of them is not 13. The
 * number 1 is Kaprekar, because 1^2 = 01, and 0 + 1 = 1.
 */
import java.util.Scanner;

class Kaprekar {
  static boolean isKaprekar(int num, int square) {
    int digits = (int) Math.log10(square) + 1;
    for (int i = 0; i < digits; i++) {
      int firstHalf = square % (int) Math.pow(10, i);
      int secondHalf = square / (int) Math.pow(10, i);

      if (firstHalf + secondHalf == num) return true;
    }

    return false;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int testCases = scanner.nextInt();

    while (testCases-- > 0) {
      int num = scanner.nextInt();
      int square = num * num;

      if (isKaprekar(num, square)) System.out.println("1");
      else System.out.println("0");
    }
  }
}
