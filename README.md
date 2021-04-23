1. Reversi is a strategy board game for two players, played on an 8×8 uncheckered board, was invented in 1883. Othello, a variant with a change to the board's initial setup, was patented in 1971.
2. Simple project at 2nd year in university.
3. Using SDL2 as CG(Computer Graphic) to demo.
4. Open App/Othello/CG.exe to play.
![image](https://user-images.githubusercontent.com/43707410/115869092-97c83800-a467-11eb-92a9-6de64e103b09.png)
5. There are 2 modes: player vs. player and player vs. bot.
6. Bot uses Minimax optimized by Alpha-Beta Pruning and a heuristic "trial and error" reward board to calculate the optimal next move.
7. Rule:
 - Square board size >= 3 (normally 8), initial setup as below image, big dots are chesses and small dots are possible valid next move:
![image](https://user-images.githubusercontent.com/43707410/115865742-f0e19d00-a462-11eb-8ce8-e0c2cc3a1aa8.png)
 - To play next move, player have to reverse opponent's chesses by cover 2 heads in horizontal or vertical or diagonal lines with single chess. Otherwise, player's move is passed.
![image](https://user-images.githubusercontent.com/43707410/115866685-381c5d80-a464-11eb-828d-14ad1c4adb09.png)
 - Play until the board is filled, the one has more chesses win the game.
![image](https://user-images.githubusercontent.com/43707410/115867617-8716c280-a465-11eb-8ebb-dad22faa6af4.png)
8. Beware, CG code has bugs.
