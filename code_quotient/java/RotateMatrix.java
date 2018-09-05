import java.util.Scanner;

class RotateMatrix {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int testCases = scanner.nextInt();

    while (testCases-- > 0) {
      int n = scanner.nextInt();

      int[][] matrix = new int[n][n];
      for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++) matrix[row][col] = scanner.nextInt();

      int mid = (n + 1) / 2;
      int temp1, temp2;

      for (int i = 0; i < mid; i++) {
        for (int j = i; j < n - i - 1; j++) {
          // First rotation.
          temp1 = matrix[j][n - i - 1];
          matrix[j][n - i - 1] = matrix[i][j];

          // Second rotation.
          temp2 = temp1;
          temp1 = matrix[n - i - 1][n - j - 1];
          matrix[n - i - 1][n - j - 1] = temp2;

          // Third rotation.
          temp2 = temp1;
          temp1 = matrix[n - j - 1][i];
          matrix[n - j - 1][i] = temp2;

          // Fourth rotation.
          matrix[i][j] = temp1;
        }
      }

      for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
          if (col == n - 1) System.out.print(matrix[row][col]);
          else System.out.print(matrix[row][col] + " ");
        }
        System.out.println();
      }
      System.out.println();
    }
  }
}
