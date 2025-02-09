package game

import (
	"fmt"
)

type Board struct {
	cells [][]Cell
}

func (b *Board) getCellFromPosition(position int) *Cell {
	var n int = len(b.cells)
	var row int = (position - 1) / n
	var col int = (position - 1) % n

	if row%2 == 1 {
		return &b.cells[row][n-1-col]
	} else {
		return &b.cells[row][col]
	}
}

func InitBoard(size int) Board {
	var b Board
	b.cells = make([][]Cell, size)
	for i := 0; i < size; i++ {
		b.cells[i] = make([]Cell, size)
	}
	return b
}

func (b *Board) move(player *Player, steps int) {
	n := len(b.cells)
	if player.currentPosition+steps >= n*n {
		return
	}
	fmt.Println("Player ", player.id, " moved from ", player.currentPosition, " to ", player.currentPosition+steps)
	player.currentPosition += steps
	cell := b.getCellFromPosition(player.currentPosition)
	if cell.jump != nil {
		fmt.Println("Player ", player.id, " jumped from ", player.currentPosition, " to ", cell.jump.end)
		player.currentPosition = cell.jump.end
	}
}
