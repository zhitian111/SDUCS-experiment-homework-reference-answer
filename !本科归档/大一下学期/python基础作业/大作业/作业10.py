def sort_strings_by_length(strings):
    sorted_strings = sorted(strings, key=lambda x: (len(x), x))
    return sorted_strings

# 测试
strings = ["apple", "banana", "pear", "orange", "fruit"]
sorted_strings = sort_strings_by_length(strings)
print(sorted_strings)