package game

type Cell struct {
	jump *Jump
}

func (c *Cell) addJump(jump *Jump) {
	c.jump = jump
}
