package main

import (
	"snakesAndLadders/snakesAndLadders/game"
)

func main() {
	// Initialize the game with 2 players, board size of 10x10, 1 dice, 5 snakes, and 5 ladders
	game.InitGame(5, 10, 3, 2, 7).Start()
}
