#pragma once

#include "Matrix.h"
#include "ParallelTaskMultiplierBase.h"
#include "Structures.h"
#include "tbb/task.h"

class ParallelTaskPerThread : public ParallelTask
{
public:
	ParallelTaskPerThread(const MultiplicationElements multiplicationElements_, const ElementsRange elements_) noexcept;
	~ParallelTaskPerThread() = default;

	tbb::task* execute() override;
private:
	// ova funkcija se koristi da pretvori 1d index u 2d index
	// posto se u zadatom ElementsRange indexi posmatraju kao da je matrica 1d niz
	[[nodiscard]] ElementIndex get2DElementIndexFrom1D(const size_t elementIndexIn1D, const size_t numberOfElementsInRow) const noexcept;

	const ElementsRange elements;
};

class ParallelTaskPerThreadMultiplier : public ParalellTaskMultiplierBase
{
public:
	ParallelTaskPerThreadMultiplier() = default;
	~ParallelTaskPerThreadMultiplier() = default;

	[[nodiscard]] static MatrixMultiplierBase* create() noexcept;

private:
	void fillTaskListForParent(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept override;
	// Posebno se popunjava N - 1 taskova zasto sto oni imaju broj elemenata / N a poslednji mora da uracuna
	// i gresku prilikom deljenja inace par poslednjih elemenata nece biti izracunato
	void fillListWithAllTasksExceptLastOne(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept;
	void fillListWithLastTask(tbb::task_list& parentsTasks, tbb::empty_task& parent, MultiplicationElements multiplicationElements) const noexcept;

	[[nodiscard]] size_t getNumberOfElementsPerThread(const size_t numberOfElements) const noexcept;
	[[nodiscard]] int getNumberOfProcessorThreads() const noexcept;
	// Racuna gresku prilikom deljenja tako sto od ukupnog broja elemenata
	// oduzme dobijeni broj elemenata po tredu kada se pomnozi sa brojem tredova
	[[nodiscard]] size_t getDividingElementsPerThreadError(const size_t numberOfElements) const noexcept;

	[[nodiscard]] int getTotalNumberOfRefCount() const noexcept;
};