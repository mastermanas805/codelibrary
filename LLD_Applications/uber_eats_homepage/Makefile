.PHONY: run test build clean format up down logs

run:
	go run main.go

test:
	go test -v -count=1 ./tests/...

build:
	go build -o bin/server main.go

format:
	go fmt ./...

clean:
	rm -rf bin/

up:
	docker compose up -d

down:
	docker compose down -v

logs:
	docker compose logs -f
