Current capabilities of the project:

    Read aspect conversions from an Obsidian vault or file, then ability to output to file.
    Identify all nodes in the quickest path between two aspects as a set, this is preloaded as history.txt
    Find potential common nodes by combining the nodes in the quickest path of all aspects to check
    Relay all fastest paths between two given aspects

Planned capabilities:

    There are two approaches to solving this minigame I will be pursuing: helping tools or game solving.
    First, I will create helpful tools to make identifying the solutions to each puzzle easier. (Completed)
    Second, there will be the simulation of the game board and a turn-based game solving algorithm aimed at being efficient with research aspects.
    Also, the research conversions will be easily modifiable
  
  Helping Tools (Completed): This will involve creating two tools:
    
    Finding common aspects between a list of aspects
    Finding reasonable paths between two aspects

  Game Solving: Simulating the game:

      Simulating a board:
        Different board sizes
        Aspect placement on the board
        Holes in the board
      Scoring moves based on maintaining the abundance of research aspects
      Determining reasonable (possible) moves based on research conversions
