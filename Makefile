.PHONY: format
format:
	find src -name '*pp' -type f | xargs clang-format -i
