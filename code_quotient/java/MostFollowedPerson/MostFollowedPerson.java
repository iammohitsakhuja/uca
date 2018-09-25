import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class MostFollowedPerson {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    String fileName = scanner.nextLine();

    HashMap<String, ArrayList<String>> map = new HashMap<>();
    ArrayList<String> names = new ArrayList<>();

    try (BufferedReader file = new BufferedReader(new FileReader(fileName))) {
      String line = null;

      while ((line = file.readLine()) != null) {
        String[] persons = line.split(" ");

        if (!map.containsKey(persons[1])) {
          ArrayList<String> followers = new ArrayList<>();
          followers.add(persons[0]);
          map.put(persons[1], followers);

          names.add(persons[1]);
        } else {
          ArrayList<String> previousFollowers = map.get(persons[1]);
          previousFollowers.add(persons[0]);
        }
      }

    } catch (IOException ex) {
      ex.printStackTrace();
    }

    int maxCount = 0;
    String mostFollowedPerson = null;
    for (String name : names) {
      ArrayList<String> followers = map.get(name);
      int count = 0;
      for (String follower : followers)
        count += map.containsKey(follower) ? map.get(follower).size() : 0;

      if (count > maxCount) {
        maxCount = count;
        mostFollowedPerson = name;
      }
    }

    System.out.println(mostFollowedPerson);
  }
}
