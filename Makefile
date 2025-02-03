.PHONY: format
format:
	find src tests -name '*pp' -type f | xargs clang-format -i
