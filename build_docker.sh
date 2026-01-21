#!/bin/bash
NAMESPACE="${1:-codebase_b72_app}"
docker build -t "$NAMESPACE" .