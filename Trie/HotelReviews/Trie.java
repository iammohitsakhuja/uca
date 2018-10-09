public class Trie {
  static final int ALPHABET_SIZE = 26;
  TrieNode root;

  private class TrieNode {
    boolean isWord;
    TrieNode[] next;

    TrieNode() {
      this.isWord = false;
      this.next = new TrieNode[ALPHABET_SIZE];
      for (int i = 0; i < ALPHABET_SIZE; i++) this.next[i] = null;
    }
  }

  public Trie() {
    this.root = new TrieNode();
  }

  public void push(String str) {
    TrieNode currNode = this.root;

    for (char character : str.toCharArray()) {
      int j = character - 'a';
      if (currNode.next[j] == null) currNode.next[j] = new TrieNode();
      currNode = currNode.next[j];
    }

    currNode.isWord = true;
  }

  public boolean contains(String str) {
    TrieNode currNode = this.root;

    for (char character : str.toCharArray()) {
      int j = character - 'a';

      if (currNode.next[j] == null) return false;

      currNode = currNode.next[j];
    }

    return currNode.isWord;
  }
}
