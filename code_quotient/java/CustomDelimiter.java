import java.util.Scanner;

class CustomDelimiter {
  public static void main(String[] args) {
    Scanner in = new Scanner("CODE delim QUOTIENT delim CODING delim BETTER delim 34");

    // Zero or more whitespace, followed by 'delim', followed by zero or more whitespace.
    in.useDelimiter("\\s*delim\\s*");

    // The delimiter breaks the input into tokens {"CODE", "QUOTIENT", "CODING", "BETTER", "34"}.
    while (in.hasNext()) {
      System.out.println(in.next());
    }
  }
}
