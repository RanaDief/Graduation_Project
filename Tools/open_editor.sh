#!/usr/bin/env bash
set -euo pipefail
project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
engine_root="${UE_ROOT:-/home/og-pearto/Applications/UnrealEngine-5.8.4}"
exec "$engine_root/Engine/Binaries/Linux/UnrealEditor" "$project_root/WordsWeNeverSaid.uproject" -ModelContextProtocolStartServer -ModelContextProtocolPort=8017
