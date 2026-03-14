package game

import "math/rand"

type Dice struct {
	count int
}

func (d *Dice) Roll() int {
	ret := 0
	for i := 0; i < d.count; i++ {
		ret += rand.Int()%6 + 1
	}
	return ret
}
