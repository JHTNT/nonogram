# Nonogram

## Build

```bash
make all # or mingw32-make with MinGW
```

## Run

需要加上包含測資的檔案路徑作為參數（**不包含副檔名**），若輸入 `one_testcase` 則會讀取 `one_testcase.in`，並將結果輸出在 `one_testcase.out`。

```
cd ./bin
./nonogram <input_file_path>
```

## Performance

測試環境：

- CPU: Intel® Core™ i5-12400
- gcc version: 12.2.0 (WinLibs MinGW-w64)
- Compile flags: `-std=c++20 -O2`

(`$n` means the `n`th testcase)

|  | `$1` | `$2` | `$3` | `$4` | `$5` | `$6` | `$7` | `$8` | `$9` | `$10` | Total (s) |
|---|---|---|---|---|---|---|---|---|---|---|---|
| `v1.0.0` | 11.043 | 0.066 |3.493  | 0.371 | 13.356 | 34.879 | 8.398 | 141.88 | 139.705 | 0.073 | 353.264 |
