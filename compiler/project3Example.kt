class Project3Example {
	val a = 5
	var c : int

	fun add (a: int, b: int) : int {
		var sum = 0
		sum = a
		for (i in 1..b) {
			sum = sum + 1
		}
		return sum
	}

	fun middleReturn(a: int, b: int) : int {
		return a+b
		println a+b
	}

	fun noReturn(a: int, b: int) {
		println(a+b)
	}

	fun main() {
		var c = middleReturn(10, 10)
		for (i in 1..add(5, 5)) {
			for (j in 1..i) {
				print "*"
			}
			println ""
		}
		if (true) {
			println ("SUCCESS")
		}
		var i = 1
		for (i in 1..add(5, 5)) {
			for (j in 1..i) {
				print "*"
			}
			println ""
		}
		while (i <= add(a, add(3, a-3))) {
			var j = 1
			while (j <= i) {
				print "*"
				j = j + 1
			}
			println ""
			i = i + 1
		}
		if (3 != a) {
			println ("OHNO")
		}
		noReturn(1, 2)
		println ((3 != a) & (1 == 2))
	}
}
