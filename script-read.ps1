function Measure-ExecutionTime {
  param (
    [scriptblock]$ScriptBlock
  )

  $executionTime = Measure-Command $ScriptBlock
  return $executionTime.TotalMilliseconds
}

$8MB = 8388608
$16MB = 16777216
$32MB = 33554432
$64MB = 67108864
$128MB = 134217728
$256MB = 268435456

$fileSizes = @(256000, 512000, 921600, 1572864)
$sSizes = @(8, 4, 2)
$bSizesLists = @(
  @($8MB, $16MB, $32MB), 
  @($16MB, $32MB, $64MB), 
  @($64MB, $128MB, $256MB), 
  @($64MB, $128MB, $256MB)
)

for ($i = 0; $i -lt $fileSizes.Count; $i++) {
  $fileSize = $fileSizes[$i]
  $bSizes = $bSizesLists[$i]

  foreach ($bSize in $bSizes) {
    foreach ($sSize in $sSizes) {
      $executionTime = Measure-ExecutionTime { 
        & ".\out\main.exe" -r ".\out\data-sorted-$fileSize-B$($bSize)-S$($sSize).bin" ".\out\data-sorted-$fileSize-B$($bSize)-S$($sSize).txt"
      }
    }
  }
}

