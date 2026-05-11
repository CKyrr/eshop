# eshop

This repository contains a fully functional, terminal-based e-shop application built in C++. Developed as a collaborative team project for the Object-Oriented Programming course, this project demonstrates the practical application of core OOP principles, data persistence, and software design.

# System Features:
The application simulates a complete e-commerce ecosystem with Role-Based Access Control:

**Administrator Controls**: Admins can seamlessly add new products, edit existing inventory (adjusting prices, stock in units/kg, categories), search the database, and view dynamic statistics (e.g., out-of-stock items, most popular products).

**Customer Experience**: Registered users can browse the catalog, manage their shopping cart (add/remove items, adjust quantities), complete checkouts, and view their detailed order history.

**Data Persistence (File I/O)**: The entire application state—including user credentials, product catalogs, live inventory tracking, and transaction histories—is persistently read from and saved to local text files.

**Smart Discount Engine**: Implemented a custom algorithmic discount system that analyzes a user's purchase history to automatically apply dynamic discounts (e.g., loyalty rewards, consecutive purchase bonuses, and category-volume discounts).


-Design Patterns & Architecture: Strictly followed Object-Oriented Programming principles, including data encapsulation, polymorphism, and code reusability.  
-Data Structures: Custom implementation of Abstract Data Types (ADTs) to efficiently manage and store mixed user roles in a unified structure.  
-Testing: Validated system integrity against a suite of automated unit tests simulating complex user inputs.
