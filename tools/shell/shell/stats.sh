#!/bin/sh

__wh_stats() {
	cd "${PRP}" || exit 0
	command -v clear >/dev/null 2>&1 && clear

	cloc --exclude-dir=build \
		--force-lang=C,h \
		--force-lang=C++,hpp \
		--fmt=2 .
}
