import ctypes

# Load the shared library (lib.so)
lib = ctypes.CDLL('./lib.so')

# Define the function prototypes
lib.initializeSearch.argtypes = []  # No arguments
lib.initializeSearch.restype = None  # No return type

# Call initializeSearch to initialize the hash map and insert names from the binary file
lib.initializeSearch()

lib.search.argtypes = [ctypes.POINTER(ctypes.c_char_p), ctypes.c_int]
lib.search.restype = ctypes.POINTER(ctypes.c_int)

search_strings = ["shiva", "ashish"]
search_strings_c = (ctypes.c_char_p * len(search_strings))(*[s.encode('utf-8') for s in search_strings])


result = lib.search(search_strings_c, len(search_strings))

# Print the search results
for i in range(len(search_strings)):
    print(f"'{search_strings[i]}' found at index: {result[i]}")