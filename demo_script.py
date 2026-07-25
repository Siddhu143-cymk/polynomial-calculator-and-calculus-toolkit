import urllib.request
import json
import time

BASE_URL = "http://127.0.0.1:8080"

def post(endpoint, payload):
    data = json.dumps(payload).encode('utf-8')
    req = urllib.request.Request(f"{BASE_URL}{endpoint}", data=data, headers={'Content-Type': 'application/json'})
    with urllib.request.urlopen(req) as resp:
        return json.loads(resp.read().decode('utf-8'))

def get(endpoint):
    req = urllib.request.Request(f"{BASE_URL}{endpoint}")
    with urllib.request.urlopen(req) as resp:
        return json.loads(resp.read().decode('utf-8'))

def main():
    print("=========================================================")
    print(" Polynomial Calculator + Calculus Toolkit E2E Demo")
    print("=========================================================")

    # Step 1: Parse input polynomials
    p1_str = "3x^2 + 2x - 5"
    p2_str = "x - 1"
    print(f"\nStep 1: Parsing Polynomial P1 = '{p1_str}' and P2 = '{p2_str}'")
    res_p1 = post("/polynomial/parse", {"expression": p1_str})
    res_p2 = post("/polynomial/parse", {"expression": p2_str})
    print(f"  P1 Parsed: {res_p1['data']['pretty']} (Degree: {res_p1['data']['degree']})")
    print(f"  P2 Parsed: {res_p2['data']['pretty']} (Degree: {res_p2['data']['degree']})")

    # Step 2: Arithmetic (Multiply P1 * P2)
    print(f"\nStep 2: Multiplying P1 * P2")
    res_mult = post("/polynomial/multiply", {"a": p1_str, "b": p2_str})
    prod_pretty = res_mult['data']['pretty']
    print(f"  P1 * P2 = {prod_pretty}")

    # Step 3: Polynomial Long Division
    print(f"\nStep 3: Long Division P1 / P2")
    res_div = post("/polynomial/divide", {"a": p1_str, "b": p2_str})
    print(f"  Quotient  = {res_div['data']['quotient']['pretty']}")
    print(f"  Remainder = {res_div['data']['remainder']['pretty']}")

    # Step 4: Symbolic Differentiation of Product
    print(f"\nStep 4: Differentiating P1 * P2 -> d/dx ({prod_pretty})")
    res_deriv = post("/calculus/derivative", {"expression": prod_pretty})
    deriv_pretty = res_deriv['data']['pretty']
    print(f"  Derivative d/dx = {deriv_pretty}")

    # Step 5: Symbolic Indefinite Integration
    print(f"\nStep 5: Indefinite Integral of P1 -> integral({p1_str}) dx with C = 10")
    res_integ = post("/calculus/integral", {"expression": p1_str, "C": 10.0})
    print(f"  Indefinite Integral = {res_integ['data']['polynomial']['pretty']}")

    # Step 6: Definite Integration
    print(f"\nStep 6: Definite Integral of P1 over [0, 2]")
    res_def = post("/calculus/integral", {"expression": p1_str, "a": 0.0, "b": 2.0})
    print(f"  Area under curve from 0 to 2 = {res_def['data']['value']}")

    # Step 7: Operation History Log Retrieval
    print(f"\nStep 7: Retrieving Persistent Thread-Safe History Log (GET /history)")
    history = get("/history")
    print(f"  Total Logged Operations: {history['count']}")
    for entry in history['history']:
        print(f"  [{entry['timestamp']}] ID #{entry['id']} - {entry['operation'].upper()} -> Input: {entry['inputs']}")

    print("\n=========================================================")
    print(" DEMO COMPLETED SUCCESSFULLY!")
    print("=========================================================")

if __name__ == "__main__":
    main()
