Remove-Item *.gcda, *.gcno, *.gcov, tests.exe -ErrorAction SilentlyContinue

$sw = [System.Diagnostics.Stopwatch]::StartNew()
Write-Host "[1/4] Compiling..."
g++ --coverage -std=c++17 tests.cpp TicTacToe.cpp catch_amalgamated.cpp -o tests.exe 2>&1 | Out-Null
$sw.Stop()
$compileTime = [math]::Round($sw.Elapsed.TotalSeconds, 2)

if ($LASTEXITCODE -ne 0) {
    Write-Host "[FAIL] Compilation failed ($compileTime`s)" -ForegroundColor Red
    exit 1
}
Write-Host "[PASS] Compilation successful ($compileTime`s)" -ForegroundColor Green

$sw = [System.Diagnostics.Stopwatch]::StartNew()
Write-Host "[2/4] Running tests..."
$jsonOutput = .\tests.exe --reporter json 2>&1 | Out-String
$testResult = $LASTEXITCODE
$sw.Stop()
$testTime = [math]::Round($sw.Elapsed.TotalSeconds, 2)

$jsonStart = $jsonOutput.IndexOf('{')
$jsonEnd = $jsonOutput.LastIndexOf('}')
if ($jsonStart -lt 0 -or $jsonEnd -lt 0) {
    Write-Host "[FAIL] Cannot find JSON in output ($testTime`s)" -ForegroundColor Red
    Write-Host $jsonOutput
    exit 1
}
$jsonText = $jsonOutput.Substring($jsonStart, $jsonEnd - $jsonStart + 1)
$json = $jsonText | ConvertFrom-Json

$passed = 0
$failed = 0

foreach ($test in $json.'test-run'.'test-cases') {
    $name = $test.'test-info'.name
    $failedAssertions = $test.totals.assertions.failed

    if ($failedAssertions -eq 0) {
        Write-Host "  [PASS] $name" -ForegroundColor Green
        $passed++
    } else {
        Write-Host "  [FAIL] $name" -ForegroundColor Red
        $failed++
    }
}

if ($testResult -eq 0) {
    Write-Host "[PASS] All tests passed ($testTime`s)" -ForegroundColor Green
} else {
    Write-Host "[FAIL] Tests failed: $failed of $($passed + $failed) ($testTime`s)" -ForegroundColor Red
    exit 1
}

$sw = [System.Diagnostics.Stopwatch]::StartNew()
Write-Host "[3/4] Measuring coverage..."
$gcovOutput = gcov -f tests-TicTacToe.cpp 2>&1 | Out-String
$sw.Stop()
$coverageTime = [math]::Round($sw.Elapsed.TotalSeconds, 2)

$match = [regex]::Match($gcovOutput, "File 'TicTacToe\.cpp'\s*\r?\n\s*Lines executed:([\d.]+)%")

if (-not $match.Success) {
    Write-Host "[FAIL] Cannot read coverage ($coverageTime`s)" -ForegroundColor Red
    exit 1
}
$percent = [double]$match.Groups[1].Value

if ($percent -ge 90) {
    Write-Host "[PASS] Coverage: $percent% ($coverageTime`s)" -ForegroundColor Green
} else {
    Write-Host "[FAIL] Coverage: $percent% (below 90%) ($coverageTime`s)" -ForegroundColor Red
    exit 1
}

$totalTime = [math]::Round($compileTime + $testTime + $coverageTime, 2)
Write-Host "[4/4] Done."
Write-Host ""
Write-Host "=========================================="
Write-Host "  BUILD:    SUCCESSFUL" -ForegroundColor Green
Write-Host "  TESTS:    PASSED ($passed/$($passed + $failed))" -ForegroundColor Green
Write-Host "  COVERAGE: $percent%" -ForegroundColor Green
Write-Host "  TIME:     $totalTime`s" -ForegroundColor Green
Write-Host "=========================================="