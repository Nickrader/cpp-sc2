message(STATUS "FetchContent: googletest")

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 9b12f749fa972d08703d8459e9bf3239617491ca
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# IDE folders
set_target_properties(gmock PROPERTIES FOLDER contrib)
set_target_properties(gmock_main PROPERTIES FOLDER contrib)
set_target_properties(gtest PROPERTIES FOLDER contrib)
set_target_properties(gtest_main PROPERTIES FOLDER contrib)
