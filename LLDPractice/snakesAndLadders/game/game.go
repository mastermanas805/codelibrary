package game

import (
	"fmt"
	"math/rand"
)

type Game struct {
	board   Board
	dice    Dice
	players []Player
	won     *Player
}

func (g *Game) addSnake() {
	n := len(g.board.cells)
	n = n * n

	start := -1
	end := -1

	for !(start > end) {
		start = rand.Int() % n
		end = rand.Int() % n
	}

	g.board.getCellFromPosition(start).addJump(&Jump{start, end})
}

func (g *Game) addLadder() {
	n := len(g.board.cells)
	n = n * n

	start := -1
	end := -1

	for !(start < end) || start >= n || end >= n {
		start = rand.Int() % n
		end = rand.Int() % n
	}

	g.board.getCellFromPosition(start).addJump(&Jump{start, end})
}

func InitGame(playerCount int, boardSize int, diceCount int, snakes int, ladders int) *Game {
	var g Game
	g.board = InitBoard(boardSize)
	g.dice = Dice{diceCount}
	g.players = make([]Player, playerCount)
	for i := 0; i < playerCount; i++ {
		g.players[i] = Player{i, 0}
	}

	for i := 0; i < snakes; i++ {
		g.addSnake()
	}

	for i := 0; i < ladders; i++ {
		g.addLadder()
	}
	return &g
}

func (g *Game) Start() {
	n := len(g.board.cells)
	n = n * n
	for g.won == nil {
		currentPlayer := &g.players[0]
		steps := g.dice.Roll()
		fmt.Println("Player ", currentPlayer.id, " rolled dice got", steps, " steps")
		g.board.move(currentPlayer, steps)
		g.players = append(g.players[1:], *currentPlayer)
		if currentPlayer.currentPosition == n-1 {
			fmt.Println("Player ", currentPlayer.id, " won!")
			g.won = currentPlayer
		}
	}
}
