#ifndef SPARSE_POLY_MAP_H
#define SPARSE_POLY_MAP_H

#include <map>
#include <functional>
#include <vector>
#include <cstddef>

/**
 * @brief Custom thin wrapper around std::map for sparse polynomial storage.
 * Maps exponent (int) -> coefficient (double).
 * Exponents are stored in descending order (highest degree first).
 */
class SparsePolyMap {
private:
    std::map<int, double, std::greater<int>> terms;

public:
    SparsePolyMap() = default;

    /**
     * @brief Set or update coefficient for a given exponent.
     * If coeff is approximately 0, the term is removed.
     */
    void setCoeff(int exp, double coeff, double eps = 1e-12);

    /**
     * @brief Get coefficient for exponent. Returns 0.0 if term does not exist.
     */
    double getCoeff(int exp) const;

    /**
     * @brief Check if exponent exists with non-zero coefficient.
     */
    bool hasTerm(int exp) const;

    /**
     * @brief Remove term at exponent.
     */
    void removeTerm(int exp);

    /**
     * @brief Clear all terms.
     */
    void clear();

    /**
     * @brief Get underlying const map.
     */
    const std::map<int, double, std::greater<int>>& getMap() const;

    /**
     * @brief Get number of non-zero terms.
     */
    size_t size() const;

    /**
     * @brief Check if map is empty (zero polynomial).
     */
    bool empty() const;

    /**
     * @brief Get highest exponent (degree). Returns 0 if empty.
     */
    int getMaxExponent() const;
};

#endif // SPARSE_POLY_MAP_H
