# Define the source files and output
$sourceFiles = @(
    "main.cpp",
    "src/Service.cpp",
    "src/Provider.cpp",
    "src/Customer.cpp",
    "src/Bill.cpp",
    "src/populateCustomer.cpp",
    "src/populateProvider.cpp",
    "src/populateService.cpp",
    "src/DataLoader.cpp"
)

$outputExecutable = "uspMain.exe"

# Compiler and flags
$compiler = "g++"
$flags = "-Wall -std=c++11"

# Create the compile command
$compileCommand = "$compiler $flags $($sourceFiles -join ' ') -o $outputExecutable"

# Print the compile command
Write-Host "Running command: $compileCommand"

# Run the compilation command
Invoke-Expression $compileCommand

# Check if the compilation was successful
if (Test-Path $outputExecutable) {
    Write-Host "Compilation successful! You can run the program using ./$outputExecutable"
} else {
    Write-Host "Compilation failed."
}
