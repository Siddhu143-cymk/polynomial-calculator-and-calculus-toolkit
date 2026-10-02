import sys
from pptx import Presentation
from pptx.util import Inches, Pt
from pptx.enum.text import PP_ALIGN
from pptx.dml.color import RGBColor
from pptx.enum.shapes import MSO_SHAPE

def create_presentation():
    prs = Presentation()
    
    # Set slide dimensions to widescreen 16:9 (13.333 x 7.5 inches)
    prs.slide_width = Inches(13.333)
    prs.slide_height = Inches(7.5)

    blank_slide_layout = prs.slide_layouts[6]

    # Theme colors
    DARK_BG = RGBColor(15, 23, 42)       # #0f172a
    CARD_BG = RGBColor(30, 41, 59)       # #1e293b
    ACCENT_CYAN = RGBColor(6, 182, 212)   # #06b6d4
    ACCENT_PURPLE = RGBColor(139, 92, 246)# #8b5cf6
    TEXT_WHITE = RGBColor(248, 250, 252) # #f8fafc
    TEXT_MUTED = RGBColor(148, 163, 184) # #94a3b8
    CARD_BORDER = RGBColor(51, 65, 85)   # #334155

    def add_background(slide):
        bg = slide.shapes.add_shape(MSO_SHAPE.RECTANGLE, 0, 0, Inches(13.333), Inches(7.5))
        bg.fill.solid()
        bg.fill.fore_color.rgb = DARK_BG
        bg.line.fill.background()
        return bg

    def add_header(slide, title_text, category_text="POLYNOMIAL CALCULATOR + CALCULUS TOOLKIT"):
        # Header category
        cat_box = slide.shapes.add_textbox(Inches(0.8), Inches(0.5), Inches(11.7), Inches(0.4))
        tf_cat = cat_box.text_frame
        tf_cat.word_wrap = True
        p_cat = tf_cat.paragraphs[0]
        p_cat.text = category_text.upper()
        p_cat.font.size = Pt(11)
        p_cat.font.bold = True
        p_cat.font.color.rgb = ACCENT_CYAN
        p_cat.font.name = "Segoe UI"

        # Slide title
        title_box = slide.shapes.add_textbox(Inches(0.8), Inches(0.8), Inches(11.7), Inches(0.8))
        tf_title = title_box.text_frame
        tf_title.word_wrap = True
        p_title = tf_title.paragraphs[0]
        p_title.text = title_text
        p_title.font.size = Pt(26)
        p_title.font.bold = True
        p_title.font.color.rgb = TEXT_WHITE
        p_title.font.name = "Segoe UI"

    # ==========================================
    # SLIDE 1: Title Slide
    # ==========================================
    slide1 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide1)

    # Accent decorative box
    dec_box = slide1.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), Inches(1.5), Inches(11.733), Inches(4.8))
    dec_box.fill.solid()
    dec_box.fill.fore_color.rgb = CARD_BG
    dec_box.line.color.rgb = ACCENT_PURPLE

    tb1 = slide1.shapes.add_textbox(Inches(1.2), Inches(2.2), Inches(10.9), Inches(3.2))
    tf1 = tb1.text_frame
    tf1.word_wrap = True

    p1 = tf1.paragraphs[0]
    p1.text = "Polynomial Calculator & Calculus Toolkit"
    p1.font.size = Pt(36)
    p1.font.bold = True
    p1.font.color.rgb = ACCENT_CYAN
    p1.font.name = "Segoe UI"

    p2 = tf1.add_paragraph()
    p2.text = "A High-Performance Layered C++17 REST API Backend & Interactive Control Dashboard"
    p2.font.size = Pt(18)
    p2.font.color.rgb = TEXT_MUTED
    p2.font.name = "Segoe UI"

    p3 = tf1.add_paragraph()
    p3.text = "\nDeveloper: Siddhu (Siddhu143-cymk)\nStack: C++17 | cpp-httplib | nlohmann/json | MinGW GCC"
    p3.font.size = Pt(14)
    p3.font.color.rgb = TEXT_WHITE
    p3.font.name = "Segoe UI"

    # ==========================================
    # SLIDE 2: Project Overview
    # ==========================================
    slide2 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide2)
    add_header(slide2, "Project Overview & Core Objectives")

    cards_data = [
        ("🎯 Primary Objective", "Build a robust backend REST API in C++ that parses, manipulates, performs arithmetic, and solves symbolic calculus operations on single-variable polynomials."),
        ("💡 Core Problem Solved", "Eliminates floating-point accumulation errors by storing exact symbolic terms (exponent -> coefficient map) for arithmetic, differentiation, and integration."),
        ("⚡ Non-Functional Guarantee", "Stateless per-request REST architecture backed by a thread-safe (std::mutex) chronological operation history queue.")
    ]

    for i, (head, body) in enumerate(cards_data):
        top_pos = Inches(1.8 + i * 1.7)
        card = slide2.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), top_pos, Inches(11.733), Inches(1.4))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = CARD_BORDER

        tf = card.text_frame
        tf.word_wrap = True
        p_head = tf.paragraphs[0]
        p_head.text = head
        p_head.font.size = Pt(18)
        p_head.font.bold = True
        p_head.font.color.rgb = ACCENT_CYAN

        p_body = tf.add_paragraph()
        p_body.text = body
        p_body.font.size = Pt(14)
        p_body.font.color.rgb = TEXT_MUTED

    # ==========================================
    # SLIDE 3: System Architecture
    # ==========================================
    slide3 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide3)
    add_header(slide3, "Layered System Architecture")

    layers = [
        ("1. Client Layer", "Interactive Web UI (index.html), Python REST Client (test_client.py), and curl CLI commands.", ACCENT_CYAN),
        ("2. API Layer", "ApiController.cpp using cpp-httplib running on http://localhost:8080 with 10 JSON endpoints.", ACCENT_PURPLE),
        ("3. Parser Layer", "PolynomialParser.cpp & Tokenizer.cpp converting expression strings to Polynomial domain objects.", ACCENT_CYAN),
        ("4. Service & Model Layer", "ArithmeticService.cpp, CalculusEngine.cpp, Polynomial.cpp, and thread-safe HistoryLog.cpp.", ACCENT_PURPLE)
    ]

    for i, (title, desc, col) in enumerate(layers):
        left_pos = Inches(0.8 + (i % 2) * 5.95)
        top_pos = Inches(1.8 + (i // 2) * 2.5)

        card = slide3.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, left_pos, top_pos, Inches(5.7), Inches(2.2))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = col

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = title
        p1.font.size = Pt(18)
        p1.font.bold = True
        p1.font.color.rgb = col

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(14)
        p2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 4: Data Structures (DSA Focus)
    # ==========================================
    slide4 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide4)
    add_header(slide4, "Data Structures Implementation (DSA)")

    dsa_items = [
        ("SparsePolyMap", "std::map<int, double, std::greater<int>>", "Sparse storage mapping Exponent -> Coefficient sorted descending. Handles sparse polynomials (e.g. x^100 + 1) in O(K) space."),
        ("CoeffVector", "std::vector<double>", "Dense array storing coefficients indexed by exponent. Used specifically for O(N) Horner's Method evaluation."),
        ("ParserStack", "std::vector<T> wrapper", "Custom Stack wrapper supporting push(), pop(), top() used during tokenizer precedence parsing."),
        ("HistoryQueue", "std::queue<HistoryEntry>", "Custom Queue wrapper for FIFO chronological operation logging.")
    ]

    for i, (name, impl, desc) in enumerate(dsa_items):
        left_pos = Inches(0.8 + (i % 2) * 5.95)
        top_pos = Inches(1.8 + (i // 2) * 2.5)

        card = slide4.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, left_pos, top_pos, Inches(5.7), Inches(2.2))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = CARD_BORDER

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = f"{name} ({impl})"
        p1.font.size = Pt(15)
        p1.font.bold = True
        p1.font.color.rgb = ACCENT_CYAN

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(13)
        p2.font.color.rgb = TEXT_MUTED

    # ==========================================
    # SLIDE 5: Object-Oriented Design (OOP)
    # ==========================================
    slide5 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide5)
    add_header(slide5, "Object-Oriented Design (OOP Principles)")

    oop_points = [
        ("Encapsulation", "The Polynomial internal term map (SparsePolyMap) is strictly private. External callers manipulate polynomials exclusively through public methods (addTerm, evaluate, toString)."),
        ("Single Responsibility Principle", "Decoupled responsibilities: Term models individual terms, Polynomial models expressions, PolynomialParser parses text, ArithmeticService handles arithmetic, CalculusEngine computes calculus."),
        ("Thread Safety Guarding", "HistoryLog wraps HistoryQueue with std::mutex and std::lock_guard to prevent race conditions during concurrent REST requests.")
    ]

    for i, (title, desc) in enumerate(oop_points):
        top_pos = Inches(1.8 + i * 1.7)
        card = slide5.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), top_pos, Inches(11.733), Inches(1.4))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = ACCENT_PURPLE

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = title
        p1.font.size = Pt(18)
        p1.font.bold = True
        p1.font.color.rgb = ACCENT_PURPLE

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(14)
        p2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 6: Algorithms - Parsing & Horner's
    # ==========================================
    slide6 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide6)
    add_header(slide6, "Core Algorithms: Parsing & Evaluation")

    algo1_text = (
        "1. Tokenizer (Lexical Analyzer):\n"
        "   Converts string '3x^4 - 2x^2 + 7x - 1' into tokens (NUMBER, VARIABLE, PLUS, MINUS, POWER).\n\n"
        "2. Recursive Descent Parser:\n"
        "   Applies operator precedence via ParserStack. Handles parentheses (x+2)(x-3), implicit multiplication (3x), unary minus, and exponentiation."
    )

    algo2_text = (
        "Horner's Method for O(N) Evaluation:\n\n"
        "   Rewrites P(x) = a0 + x(a1 + x(a2 + ... + x(an)))\n\n"
        "   Evaluates polynomial in linear O(N) time with 0 redundant calls to pow()."
    )

    card1 = slide6.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), Inches(1.8), Inches(5.7), Inches(5.0))
    card1.fill.solid()
    card1.fill.fore_color.rgb = CARD_BG
    card1.line.color.rgb = ACCENT_CYAN

    tf1 = card1.text_frame
    tf1.word_wrap = True
    p_h1 = tf1.paragraphs[0]
    p_h1.text = "Expression Parsing Algorithm"
    p_h1.font.size = Pt(18)
    p_h1.font.bold = True
    p_h1.font.color.rgb = ACCENT_CYAN

    p_b1 = tf1.add_paragraph()
    p_b1.text = algo1_text
    p_b1.font.size = Pt(13)
    p_b1.font.color.rgb = TEXT_WHITE

    card2 = slide6.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0))
    card2.fill.solid()
    card2.fill.fore_color.rgb = CARD_BG
    card2.line.color.rgb = ACCENT_PURPLE

    tf2 = card2.text_frame
    tf2.word_wrap = True
    p_h2 = tf2.paragraphs[0]
    p_h2.text = "Fast O(N) Evaluation"
    p_h2.font.size = Pt(18)
    p_h2.font.bold = True
    p_h2.font.color.rgb = ACCENT_PURPLE

    p_b2 = tf2.add_paragraph()
    p_b2.text = algo2_text
    p_b2.font.size = Pt(14)
    p_b2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 7: Algorithms - Arithmetic & Division
    # ==========================================
    slide7 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide7)
    add_header(slide7, "Core Algorithms: Arithmetic & Long Division")

    arith_items = [
        ("Addition & Subtraction", "Iterates terms and sums/subtracts matching exponents: c1 + c2 at exponent e."),
        ("Multiplication", "Double nested loop multiplying coefficients (c1 * c2) and adding exponents (e1 + e2)."),
        ("Polynomial Long Division", "Iteratively divides leading term of dividend by leading term of divisor, returning exact Quotient and Remainder polynomials. Protects against zero divisor.")
    ]

    for i, (title, desc) in enumerate(arith_items):
        top_pos = Inches(1.8 + i * 1.7)
        card = slide7.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), top_pos, Inches(11.733), Inches(1.4))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = CARD_BORDER

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = title
        p1.font.size = Pt(18)
        p1.font.bold = True
        p1.font.color.rgb = ACCENT_CYAN

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(14)
        p2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 8: Algorithms - Calculus Engine
    # ==========================================
    slide8 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide8)
    add_header(slide8, "Calculus Engine & Root Finding")

    calc_data = [
        ("Symbolic Differentiation", "Applies exact Power Rule: d/dx (c * x^n) = (c * n) * x^(n-1). Constant terms (n=0) vanish."),
        ("Symbolic & Definite Integration", "Applies Power Rule: integral (c * x^n) dx = (c / (n+1)) * x^(n+1) + C. Definite integral calculates F(b) - F(a)."),
        ("Newton-Raphson Root Finding", "Iteratively updates x_(n+1) = x_n - f(x_n)/f'(x_n). Automatically falls back to Bisection Search when derivative f'(x_n) ≈ 0.")
    ]

    for i, (title, desc) in enumerate(calc_data):
        top_pos = Inches(1.8 + i * 1.7)
        card = slide8.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), top_pos, Inches(11.733), Inches(1.4))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = ACCENT_PURPLE

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = title
        p1.font.size = Pt(18)
        p1.font.bold = True
        p1.font.color.rgb = ACCENT_PURPLE

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(14)
        p2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 9: REST API & Web Dashboard
    # ==========================================
    slide9 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide9)
    add_header(slide9, "REST API Endpoints & Interactive Web UI")

    api_text = (
        "REST API Server (http://localhost:8080):\n\n"
        "• GET /                   - Serves interactive Web UI\n"
        "• POST /polynomial/parse  - Parses polynomial to JSON\n"
        "• POST /polynomial/add    - Polynomial addition\n"
        "• POST /polynomial/divide - Long division (Quotient + Remainder)\n"
        "• POST /calculus/derivative- Symbolic differentiation\n"
        "• POST /calculus/integral - Indefinite & Definite integration\n"
        "• POST /calculus/roots    - Root finding algorithm\n"
        "• GET /history            - Thread-safe history log"
    )

    card = slide9.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), Inches(1.8), Inches(11.733), Inches(5.0))
    card.fill.solid()
    card.fill.fore_color.rgb = CARD_BG
    card.line.color.rgb = ACCENT_CYAN

    tf = card.text_frame
    tf.word_wrap = True
    p1 = tf.paragraphs[0]
    p1.text = "API Schema & Integration"
    p1.font.size = Pt(20)
    p1.font.bold = True
    p1.font.color.rgb = ACCENT_CYAN

    p2 = tf.add_paragraph()
    p2.text = api_text
    p2.font.size = Pt(14)
    p2.font.color.rgb = TEXT_WHITE

    # ==========================================
    # SLIDE 10: Verification & Conclusion
    # ==========================================
    slide10 = prs.slides.add_slide(blank_slide_layout)
    add_background(slide10)
    add_header(slide10, "Verification, Testing & Conclusion")

    conc_data = [
        ("✅ Build System", "Compiled with MinGW GCC 16.1 C++17 compiler via CMake & build.bat script."),
        ("✅ Unit & Integration Testing", "Passed 100% unit tests (test_models, test_parser, test_arithmetic, test_calculus, test_history) & REST API suite (test_client.py)."),
        ("✅ Open-Source Repository", "Published on GitHub: Siddhu143-cymk/polynomial-calculator-and-calculus-toolkit.")
    ]

    for i, (title, desc) in enumerate(conc_data):
        top_pos = Inches(1.8 + i * 1.7)
        card = slide10.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(0.8), top_pos, Inches(11.733), Inches(1.4))
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = ACCENT_PURPLE

        tf = card.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = title
        p1.font.size = Pt(18)
        p1.font.bold = True
        p1.font.color.rgb = ACCENT_CYAN

        p2 = tf.add_paragraph()
        p2.text = desc
        p2.font.size = Pt(14)
        p2.font.color.rgb = TEXT_WHITE

    output_file = "Polynomial_Calculator_Presentation.pptx"
    prs.save(output_file)
    print(f"Presentation saved successfully as '{output_file}'")

if __name__ == "__main__":
    create_presentation()
