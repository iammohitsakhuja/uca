import java.util.Scanner;

class SpiralMatrix {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int m = scanner.nextInt();
    int n = scanner.nextInt();

    int[][] matrix = new int[m][n];
    for (int row = 0; row < m; row++)
      for (int col = 0; col < n; col++) matrix[row][col] = scanner.nextInt();

    int left = 0;
    int right = 0;
    int index = 0;
    int length = m * n;
    while (index < length) {
      for (int k = left; k < n - right; k++) {
        System.out.println(matrix[left][k]);
        index++;
      }

      if (index >= length) break;

      left++;

      for (int k = left; k < m - right; k++) {
        System.out.println(matrix[k][n - right - 1]);
        index++;
      }

      if (index >= length) break;

      for (int k = n - left - 1; k >= right; k--) {
        System.out.println(matrix[m - left][k]);
        index++;
      }

      if (index >= length) break;

      right++;

      for (int k = m - left - 1; k >= right; k--) {
        System.out.println(matrix[k][right - 1]);
        index++;
      }
    }
  }
}
