#!/bin/bash
start=$(date +%s)  # 记录开始时间（秒+毫秒）

./muPos CryMu.mac

end=$(date +%s)    # 记录结束时间（秒+毫秒）
runtime=$(( (end - start) ))  # 计算运行时间

echo "running $runtime s"

