package service

import (
	"math"
	"github.com/mmcloughlin/geohash"
)

// Constants for precision and search radius
const (
	// Length 5 Geohash is roughly 4.9km x 4.9km bounding box.
	// This is commonly used for hyper-local nearby searches.
	GeohashPrecision = 5 
	
	// Max distance to return restaurant to user in km
	MaxSearchRadiusKm = 5.0
)

// EncodeGeohash generates a standard 12-char geohash
func EncodeGeohash(lat, lng float64) string {
	return geohash.Encode(lat, lng)
}

// GetNeighboringPrefixes returns the 9 relevant prefixes for full area coverage.
// It returns the prefix for the given lat/lng, plus its 8 surrounding neighbors.
func GetNeighboringPrefixes(lat, lng float64, precision uint) []string {
	// Calculate the central geohash
	center := geohash.EncodeWithPrecision(lat, lng, precision)
	
	// mmcloughlin/geohash provides a method to get 8 neighbors
	neighbors := geohash.Neighbors(center)

	prefixes := make([]string, 0, 9)
	prefixes = append(prefixes, center)
	prefixes = append(prefixes, neighbors...)
	
	return prefixes
}

// Haversine calculates distance between two points on Earth in km.
func Haversine(lat1, lon1, lat2, lon2 float64) float64 {
	const earthRadiusKm = 6371.0

	// convert degrees to radians
	dLat := (lat2 - lat1) * (math.Pi / 180.0)
	dLon := (lon2 - lon1) * (math.Pi / 180.0)

	// convert to radians
	lat1 = lat1 * (math.Pi / 180.0)
	lat2 = lat2 * (math.Pi / 180.0)

	// apply formulae
	a := math.Pow(math.Sin(dLat/2), 2) +
		math.Pow(math.Sin(dLon/2), 2)*
			math.Cos(lat1)*math.Cos(lat2)
	
	c := 2 * math.Asin(math.Sqrt(a))
	
	return earthRadiusKm * c
}
