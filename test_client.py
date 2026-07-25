import urllib.request
import json
import time
import sys

BASE_URL = "http://127.0.0.1:8080"

def post_json(endpoint, payload):
    url = f"{BASE_URL}{endpoint}"
    data = json.dumps(payload).encode('utf-8')
    req = urllib.request.Request(url, data=data, headers={'Content-Type': 'application/json'})
    try:
        with urllib.request.urlopen(req) as resp:
            return resp.status, json.loads(resp.read().decode('utf-8'))
    except urllib.error.HTTPError as e:
        return e.code, json.loads(e.read().decode('utf-8'))

def get_json(endpoint):
    url = f"{BASE_URL}{endpoint}"
    req = urllib.request.Request(url)
    try:
        with urllib.request.urlopen(req) as resp:
            return resp.status, json.loads(resp.read().decode('utf-8'))
    except urllib.error.HTTPError as e:
        return e.code, json.loads(e.read().decode('utf-8'))

def run_api_tests():
    print("==================================================")
    print(" Running REST API Endpoint Verification Suite")
    print("==================================================")

    # 1. /polynomial/parse
    print("\n1. Testing POST /polynomial/parse...")
    status, res = post_json("/polynomial/parse", {"expression": "3x^4 - 2x^2 + 7x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["status"] == "success"
    assert res["data"]["pretty"] == "3x^4 - 2x^2 + 7x - 1"

    # 2. /polynomial/add
    print("\n2. Testing POST /polynomial/add...")
    status, res = post_json("/polynomial/add", {"a": "3x^2 + 2x - 5", "b": "x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["pretty"] == "3x^2 + 3x - 6"

    # 3. /polynomial/subtract
    print("\n3. Testing POST /polynomial/subtract...")
    status, res = post_json("/polynomial/subtract", {"a": "3x^2 + 2x - 5", "b": "x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["pretty"] == "3x^2 + x - 4"

    # 4. /polynomial/multiply
    print("\n4. Testing POST /polynomial/multiply...")
    status, res = post_json("/polynomial/multiply", {"a": "3x^2 + 2x - 5", "b": "x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["pretty"] == "3x^3 - x^2 - 7x + 5"

    # 5. /polynomial/divide
    print("\n5. Testing POST /polynomial/divide...")
    status, res = post_json("/polynomial/divide", {"a": "3x^2 + 2x - 5", "b": "x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200
    assert res["data"]["quotient"]["pretty"] == "3x + 5"
    assert res["data"]["remainder"]["pretty"] == "0"

    # Test division by zero
    status, res = post_json("/polynomial/divide", {"a": "3x^2 + 2x - 5", "b": "0"})
    print(f"Status: {status} (Expected 400 for Div Zero), Message: {res.get('message')}")
    assert status == 400

    # 6. /polynomial/evaluate
    print("\n6. Testing POST /polynomial/evaluate...")
    status, res = post_json("/polynomial/evaluate", {"expression": "3x^2 + 2x - 5", "x": 2.0})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["value"] == 11.0

    # 7. /calculus/derivative
    print("\n7. Testing POST /calculus/derivative...")
    status, res = post_json("/calculus/derivative", {"expression": "3x^4 - 2x^2 + 7x - 1"})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["pretty"] == "12x^3 - 4x + 7"

    # 8. /calculus/integral (Indefinite & Definite)
    print("\n8. Testing POST /calculus/integral (Indefinite & Definite)...")
    status, res = post_json("/calculus/integral", {"expression": "3x^2 + 2x - 5", "C": 10.0})
    print(f"Indefinite Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and res["data"]["polynomial"]["pretty"] == "x^3 + x^2 - 5x + 10"

    status, res = post_json("/calculus/integral", {"expression": "3x^2 + 2x - 5", "a": 0.0, "b": 2.0})
    print(f"Definite Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and abs(res["data"]["value"] - 2.0) < 1e-6

    # 9. /calculus/roots
    print("\n9. Testing POST /calculus/roots...")
    status, res = post_json("/calculus/roots", {"expression": "x^2 - 4", "guess": 1.0})
    print(f"Status: {status}, Response: {json.dumps(res, indent=2)}")
    assert status == 200 and len(res["data"]["roots"]) > 0

    # 10. /history
    print("\n10. Testing GET /history...")
    status, res = get_json("/history")
    print(f"Status: {status}, History count: {res['count']}")
    assert status == 200 and res["count"] >= 9

    print("\n==================================================")
    print(" ALL 10 REST API ENDPOINTS VERIFIED SUCCESSFULLY!")
    print("==================================================")

if __name__ == "__main__":
    run_api_tests()
