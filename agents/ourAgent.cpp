#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Define a clock to avoid timing out
using Clock = std::chrono::steady_clock;

struct Move {
  int x, y;
};

// to process incoming messages
static std::vector<std::string> split(const std::string &s, char delimeter) {
  std::vector<std::string> out;
  std::string current;
  for (char ch : s) {
    if (ch == delimeter) {
      out.push_back(current);
      current.clear();
    } else {
      current += ch;
    }
  }
  out.push_back(current);
  return out;
}

// opposite colour (when they swap on first move)
static std::string opp(const std::string &c) {
  return c == "R" ? "B" : (c == "B" ? "R" : "None");
}

class Agent {
private:
  std::string colour_;
  int n_;    // board size
  int turn_; // turn number
  std::mt19937 rng_;

public:
  Agent(std::string colour, int size) : colour_(std::move(colour)), n_(size) {
    rng_.seed(std::random_device{}());
  }

  void run() {
    std::ios::sync_with_stdio(false);
    std::string line;
    while (std::getline(std::cin, line)) {
      if (!handle(line))
        break;
    }
  }

private:
  // handle an incoming message
  bool handle(const std::string &line) {
    auto f = split(line, ';');
    // usually has 4 elements
    if (f.size() < 4)
      return false;
    const std::string &type = f[0];
    std::vector<std::string> board = split(f[2], ',');
    turn_ = std::stoi(f[3]);

    if (type == "START") {
      if (colour_ == "R")
        makeMove(board);
    } else if (type == "CHANGE") {
      makeMove(board);
    } else if (type == "SWAP") {
      colour_ = opp(colour_);
      makeMove(board);
    } else {
      return false;
    }
    return true;
  }

  void send(const std::string &msg) { std::cout << msg << "\n" << std::flush; }

  // TODO: replace with swap heuristic
  bool shouldSwap(const std::vector<std::string> &board) { return false; }

  void makeMove(const std::vector<std::string> &board) {
    if (turn_ == 2 && shouldSwap(board)) {
      colour_ = opp(colour_);
      send("-1,-1");
      return;
    }
    Move move = chooseMove(board);
    send(std::to_string(move.x) + "," + std::to_string(move.y));
  }

  // TODO: replace with actual move calculation
  Move chooseMove(const std::vector<std::string> &board) {
    auto deadline = Clock::now() + std::chrono::milliseconds(5000);

    (void)deadline; // TODO: time management functionality

    std::vector<Move> available_moves;

    for (int i = 0; i < n_; i++)
      for (int j = 0; j < n_; j++)
        if (board[i][j] == '0')
          available_moves.push_back({i, j});

    if (available_moves.empty()) {
      return {-1, -1}; // No available moves
    }

    return available_moves[rng_() %
                           available_moves.size()]; // TODO: CHANGE THIS TO
                                                    // SOMETHING SMARTER
  }
};
