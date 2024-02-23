#pragma once

#include <unordered_map>
#include <tuple>
#include <algorithm>

#pragma once

#include <unordered_map>
#include <tuple>
#include <algorithm>

/// Struct representing a position with two integer coordinates.
///
/// Provides an equality comparison and hash function.
struct Pos final
{
    /// X coordinate of the position.
    int x{};

    /// Y coordinate of the position.
    int y{};

    /// Equality comparison between positions based on their coordinates.
    /// @param other The position to compare against.
    /// @return True if both positions have equal coordinates, false otherwise.
    bool operator==(const Pos& other) const noexcept
    {
        return other.x == x && other.y == y;
    }
};

/// Hash functor for `Pos`.
///
/// Combines hashes from each coordinate using XOR operation.
struct PosHash final
{
    /// Hashes a given position.
    /// @param r Position to be hashed.
    /// @return A unique identifier for the position.
    size_t operator()(const Pos& r) const noexcept
    {
        return std::hash<int>()(r.x) ^ std::hash<int>()(r.y);
    }
};

/// Template class implementing sparse matrices.
///
/// Each element is represented as a proxy object that allows accessing elements at specific indices.
///
/// \tparam T Type of values stored in the matrix.
/// \tparam Default Value used when there are no entries at certain indices (default value).
template <typename T, T Default>
class SparseMatrix final
{
public:
    /// Inner class representing proxies to access individual elements.
    class Proxy final
    {
    public:
        /// Constructor initializes the proxy with reference to the containing matrix and its index.
        /// @param m Reference to the containing matrix.
        /// @param row Index of the desired row.
        Proxy(SparseMatrix& m, int row) noexcept :
            matrix(m),
            x(row)
        {}

        /// Accessor allowing modification of the corresponding element.
        /// @param y Column index of the desired entry.
        /// @return Reference to the element at specified location.
        T& operator[](int y) noexcept
        {
            return matrix.data[{x, y}];
        }

    private:
        SparseMatrix& matrix;   ///< Reference to the containing matrix.
        int x;                  ///< Row index of this proxy.
    }; // Proxy

    /// Returns a proxy object providing access to the element at the specified index.
    /// @param x Desired row index.
    /// @return Proxy object for the requested index.
    Proxy operator[](int x) noexcept
    {
        return Proxy(*this, x);
    }

    /// Counts the number of non-default entries in the matrix.
    /// @return Number of non-default entries.
    [[nodiscard]] size_t size() const noexcept
    {
        return std::count_if(data.begin(), data.end(), [](const auto& pair) noexcept
        {
            return pair.second != Default;
        });
    }

    class iterator final
    {
    public:
        explicit iterator(typename std::unordered_map<Pos, T, PosHash>::iterator iter) noexcept :
            it(iter)
        {
        }

        bool operator!=(const iterator& other) const noexcept
        {
            return it != other.it;
        }

        void operator++() noexcept
        {
            ++it;
        }

        std::tuple<int, int, T> operator*() const noexcept
        {
            return { it->first.x, it->first.y, it->second };
        }

    private:
        typename std::unordered_map<Pos, T, PosHash>::iterator it;
    }; // iterator

    iterator begin() noexcept
    {
        return iterator(data.begin());
    }

    iterator end() noexcept
    {
        return iterator(data.end());
    }

private:
    std::unordered_map<Pos, T, PosHash> data;
};
