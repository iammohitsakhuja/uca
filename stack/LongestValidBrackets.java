import java.util.Scanner;
import java.util.Stack;

class StackNode {
  char ch;
  int index;

  StackNode(char ch, int index) {
    this.ch = ch;
    this.index = index;
  }
}

class LongestValidBrackets {
  static char returnOpposingBracket(char bracket) {
    switch (bracket) {
      case '}':
        return '{';
      case ')':
        return '(';
      case ']':
        return '[';
    }

    return 0;
  }

  static int longestValidBrackets(String brackets) {
    Stack<StackNode> s = new Stack<>();

    int max = 0;
    int curr = 0;
    for (int i = 0; i < brackets.length(); i++) {
      char ch = brackets.charAt(i);

      if (ch == '{' || ch == '[' || ch == '(') {
        StackNode node = new StackNode(ch, i);
        s.push(node);
        continue;
      }

      // match will only contain closing brackets or '0'.
      char match = returnOpposingBracket(ch);
      if (!s.empty() && s.peek().ch == match) {
        curr = i - s.peek().index + 1;
        if (curr > max) max = curr;
        s.pop();
      } else {
        /* Since it is a closing bracket and it didn't match, stack can be emptied. */
        s.clear();
      }
    }

    return max;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    String brackets;
    System.out.print("Enter a string consisting of brackets: ");
    brackets = scanner.nextLine();

    System.out.println("Length of longest valid brackets: " + longestValidBrackets(brackets));
  }
}
