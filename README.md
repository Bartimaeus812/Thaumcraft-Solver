Current capabilities of the project:
  Read aspect conversions from an Obsidian vault or file, then ability to output to file
  Search for the quickest path between two aspects using Dijkstra's Algorithm

Planned capabilities:
  There are two different approaches to solving this research: helping tools or game solving.
  First I will create helping tools since I have little ai experience.

  Helping Tools:
    This will involve creating two tools: finding common aspects between a list of aspects, and finding reasonable paths between two aspects

  Game Solving
    Second will be the simulation of the game board with turn based game solving to be efficient with research aspects
    This will involve:
      simulating a board:
        Aspect placement on the board
        Holes in the board
      scoring moves based on maintaining abundance of research aspects
      determining reasonable (possible) moves based on research conversions
