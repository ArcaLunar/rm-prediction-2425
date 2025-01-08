file(REMOVE_RECURSE
  "libFilter.a"
  "libFilter.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Filter.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
