import java.util.Scanner;

class Date {
  private int day;
  private int month;

  public Date(int month, int day) {
    this.month = month;
    this.day = day;
  }

  public int monthDays(int month) {
    int days = 0;

    switch (month) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        days = 31;
        break;
      case 2:
        days = 28;
        break;
      case 4:
      case 6:
      case 9:
      case 11:
        days = 30;
        break;
      default:
        days = 0;
    }

    return days;
  }

  public int daysInMonth() {
    return monthDays(month);
  }

  public int getDay() {
    return day;
  }

  public int getMonth() {
    return month;
  }

  public void nextDay() {
    this.day++;
    if (this.day > this.daysInMonth()) {
      this.month++;
      this.day = 1;
    }
    if (this.month > 12) {
      this.month = 1;
    }
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append(month).append("/").append(day);
    return sb.toString();
  }

  public int absoluteDay() {
    int days = 0;

    for (int i = 1; i < this.month; i++) {
      days += monthDays(i);
    }

    return days + this.day;
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);

    int month = scanner.nextInt();
    int day = scanner.nextInt();

    Date d = new Date(month, day);

    // First thing is absolute day.
    System.out.println(d.absoluteDay());

    // Second is daysInMonth
    System.out.println(d.daysInMonth());

    // Third is getDay
    System.out.println(d.getDay());

    // Fourth is getMonth
    System.out.println(d.getMonth());

    d.nextDay();

    System.out.println(d.getDay());
    System.out.println(d.getMonth());

    // Last thing is to string.
    System.out.println(d.toString());
  }
}
