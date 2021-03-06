#pragma once
/* MAT.h
 *
 * Copyright (C) 2017,2018 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

/*
	Some functions that are included below.
*/

/*
	From here on alphabetical order.
*/

inline void MATadd_inplace (MAT const& x, double addend) noexcept {
	VECadd_inplace (asvector (x), addend);
}
inline void MATadd_inplace (MAT const& x, constMAT const& y) noexcept {
	VECadd_inplace (asvector (x), asvector (y));
}
inline void MATadd_preallocated (const MAT& target, const constMAT& x, double addend) noexcept {
	Melder_assert (x.nrow == target.nrow && x.ncol == target.ncol);
	VECadd_preallocated (asvector (target), asvector (x), addend);
}
inline autoMAT MATadd (const constMAT& x, double addend) {
	autoMAT result = MATraw (x.nrow, x.ncol);
	MATadd_preallocated (result.get(), x, addend);
	return result;
}
inline void MATadd_preallocated (const MAT& target, const constMAT& x, const constMAT& y) noexcept {
	Melder_assert (x.nrow == target.nrow && x.ncol == target.ncol);
	Melder_assert (y.nrow == x.nrow && y.ncol == x.ncol);
	VECadd_preallocated (asvector (target), asvector (x), asvector (y));
}
inline autoMAT MATadd (const constMAT& x, const constMAT& y) noexcept {
	autoMAT result = MATraw (x.nrow, x.ncol);
	MATadd_preallocated (result.get(), x, y);
	return result;
}

/*
	Make the average of each column zero.
		a[i][j] -= a[.][j]
*/
extern void MATcentreEachColumn_inplace (const MAT& x) noexcept;

/*
	Make the average of each row zero.
		a[i][j] -= a[i][.]
*/
extern void MATcentreEachRow_inplace (const MAT& x) noexcept;

/*
	Make the average of every column and every row zero.
		a[i][j] += - a[i][.] - a[.][j] + a[.][.]
*/
extern void MATdoubleCentre_inplace (const MAT& x) noexcept;

extern void MATmtm_preallocated (const MAT& target, const constMAT& x) noexcept;
inline autoMAT MATmtm (const constMAT& x) {
	autoMAT result = MATraw (x.ncol, x.ncol);
	MATmtm_preallocated (result.get(), x);
	return result;
}

/*
	Precise matrix multiplication, using pairwise summation.
*/
extern void MATVUmul_ (const MATVU& target, const constMATVU& x, const constMATVU& y) noexcept;
inline void MATVUmul  (const MATVU& target, const constMATVU& x, const constMATVU& y) noexcept {
	Melder_assert (target.nrow == x.nrow);
	Melder_assert (target.ncol == y.ncol);
	Melder_assert (x.ncol == y.nrow);
	MATVUmul_ (target, x, y);
}
inline autoMAT MATmul (const constMATVU& x, const constMATVU& y) {
	autoMAT result = MATraw (x.nrow, y.ncol);
	MATVUmul (result.all(), x, y);
	return result;
}
/*
	Rough matrix multiplication, using an in-cache inner loop if that is faster.
*/
extern void MATVUmul_fast_ (const MATVU& target, const constMATVU& x, const constMATVU& y) noexcept;
inline void MATVUmul_fast  (const MATVU& target, const constMATVU& x, const constMATVU& y) noexcept {
	Melder_assert (target.nrow == x.nrow);
	Melder_assert (target.ncol == y.ncol);
	Melder_assert (x.ncol == y.nrow);
	MATVUmul_fast_ (target, x, y);
}
inline autoMAT MATmul_fast (const constMAT& x, const constMAT& y) {
	autoMAT result = MATraw (x.nrow, y.ncol);
	MATVUmul_fast (result.all(), x, y);
	return result;
}

inline void MATmultiply_inplace (const MAT& x, double factor) noexcept {
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] *= factor;
}

void MATouter_preallocated (const MAT& target, const constVEC& x, const constVEC& y);
extern autoMAT MATouter (const constVEC& x, const constVEC& y);

extern autoMAT MATpeaks (const constVEC& x, bool includeEdges, int interpolate, bool sortByHeight);

inline autoMAT MATrandomGauss (integer nrow, integer ncol, double mu, double sigma) {
	autoMAT result = MATraw (nrow, ncol);
	for (integer irow = 1; irow <= nrow; irow ++)
		for (integer icol = 1; icol <= ncol; icol ++)
			result [irow] [icol] = NUMrandomGauss (mu, sigma);
	return result;
}

inline void MATsin_inplace (const MAT& x) noexcept {
	VECsin_inplace (asvector (x));
}

inline void MATsubtract_inplace (const MAT& x, double number) noexcept {
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] -= number;
}
inline void MATsubtract_inplace (const MAT& x, const constVEC& y) noexcept {
	Melder_assert (x.ncol == y.size);
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] -= y [icol];
}
inline void MATsubtractReversed_inplace (const MAT& x, double number) noexcept {
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] = number - x [irow] [icol];
}
inline void MATsubtract_inplace (const MAT& x, const constMAT& y) noexcept {
	Melder_assert (y.nrow == x.nrow && y.ncol == x.ncol);
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] -= y [irow] [icol];
}
inline void MATsubtractReversed_inplace (const MAT& x, const constMAT& y) noexcept {
	Melder_assert (y.nrow == x.nrow && y.ncol == x.ncol);
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			x [irow] [icol] = y [irow] [icol] - x [irow] [icol];
}
inline autoMAT MATsubtract (const constMAT& x, double y) {
	auto result = MATraw (x.nrow, x.ncol);
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			result [irow] [icol] = x [irow] [icol] - y;
	return result;
}
inline autoMAT MATsubtract (double x, const constMAT& y) {
	auto result = MATraw (y.nrow, y.ncol);
	for (integer irow = 1; irow <= y.nrow; irow ++)
		for (integer icol = 1; icol <= y.ncol; icol ++)
			result [irow] [icol] = x - y [irow] [icol];
	return result;
}
inline autoMAT MATsubtract (const constMAT& x, const constMAT& y) {
	Melder_assert (y.nrow == x.nrow && y.ncol == x.ncol);
	auto result = MATraw (x.nrow, x.ncol);
	for (integer irow = 1; irow <= x.nrow; irow ++)
		for (integer icol = 1; icol <= x.ncol; icol ++)
			result [irow] [icol] = x [irow] [icol] - y [irow] [icol];
	return result;
}

inline void MATtranspose_inplace_mustBeSquare (const MAT& x) noexcept {
	Melder_assert (x.nrow == x.ncol);
	integer n = x.nrow;
	for (integer i = 1; i < n; i ++)
		for (integer j = i + 1; j <= n; j ++)
			std::swap (x [i] [j], x [j] [i]);
}
inline void MATtranspose_preallocated (const MAT& target, const constMAT& x) noexcept {
	Melder_assert (x.nrow == target.ncol && x.ncol == target.nrow);
	for (integer irow = 1; irow <= target.nrow; irow ++)
		for (integer icol = 1; icol <= target.ncol; icol ++)
			target [irow] [icol] = x [icol] [irow];
}
inline autoMAT MATtranspose (const constMAT& x) {
	autoMAT result = MATraw (x.ncol, x.nrow);
	MATtranspose_preallocated (result.get(), x);
	return result;
}

/* End of file MAT.h */
