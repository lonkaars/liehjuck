#!/bin/python3
import json, jsonschema, argparse
parser = argparse.ArgumentParser()
parser.add_argument("jdscn_file")
args = parser.parse_args()
with open('./jdscn.schema.json', 'r') as schema_file:
    schema = json.loads(schema_file.read())
with open(args.jdscn_file, 'r') as jdscn_file:
    jsonschema.validate(json.loads(jdscn_file.read()), schema)

