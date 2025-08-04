<script lang="ts">
	type Book = {
		identifier: number;
		title: string;
		author: string;
		genre: string;
		YearPublished: number;
	};
	let toDelete: Book = { identifier: 0, title: "", author: "", genre: "", YearPublished: 0 };
	let toInsert: Book = { identifier: 0, title: "", author: "", genre: "", YearPublished: 0 };
	let toUpdate: Book = { identifier: 0, title: "", author: "", genre: "", YearPublished: 0 };
	let success_msg: string = "";
	let failure_msg: string = "";
	let fetchBooks : Book[] = [];

	async function create_item(itemToCreate: Book) {
		const intermediate = JSON.stringify(itemToCreate);
		const result = await window.saucer.exposed.create_book(intermediate);

		if (result) {
			success_msg = "Item created successfully!"
			setTimeout(() => success_msg = "", 3000);
		} else {
			failure_msg = "Item creation failed!"
			setTimeout(() => failure_msg = "", 3000);
		}
	}

	async function getBooks() {
		let items: string = await window.saucer.exposed.fetchItems();

		if (!items || items === "null") {
			failure_msg = "You don't have any book in stock!";
			setTimeout(() => failure_msg = "", 3000);
			fetchBooks = [];
		} else {
			success_msg = "Items fetched successfully!";
			setTimeout(() => success_msg = "", 3000);
			fetchBooks = JSON.parse(items) as Book[];
		}
	}

	async function updateBook(itemToUpdate: Book){
		const intermediate = JSON.stringify(itemToUpdate);
		const result = await window.saucer.exposed.update_book(intermediate);

		if (result) {
			success_msg = "Item updated successfully!"
			setTimeout(() => success_msg = "", 3000);
		} else {
			failure_msg = "Item update failed!"
			setTimeout(() => failure_msg = "", 3000);
		}
	}

	async function deleteBook(itemToDelete: Book){
		const intermediate = JSON.stringify(itemToDelete);
		const result = await window.saucer.exposed.delete_book(intermediate);

		if (result) {
			success_msg = "Item deleted successfully!"
			setTimeout(() => success_msg = "", 3000);
		} else {
			failure_msg = "Item deletion failed!"
			setTimeout(() => failure_msg = "", 3000);
		}
	}
</script>
<main class="p-4 max-w-4xl mx-auto">
	<h1 class="text-2xl font-bold mb-4">📚 Book Manager</h1>

	<!-- Alerts -->
	{#if success_msg}
		<div class="bg-green-100 border border-green-400 text-green-700 px-4 py-2 mb-3 rounded">
			{success_msg}
		</div>
	{/if}
	{#if failure_msg}
		<div class="bg-red-100 border border-red-400 text-red-700 px-4 py-2 mb-3 rounded">
			{failure_msg}
		</div>
	{/if}

	<!-- Create Form -->
	<div class="mb-6 bg-gray-50 p-4 rounded shadow">
		<h2 class="text-lg font-semibold mb-2">Add a New Book</h2>
		<div class="grid grid-cols-2 gap-4">
			<input bind:value={toInsert.title} placeholder="Title" class="border p-2 rounded" />
			<input bind:value={toInsert.author} placeholder="Author" class="border p-2 rounded" />
			<input bind:value={toInsert.genre} placeholder="Genre" class="border p-2 rounded" />
			<input bind:value={toInsert.YearPublished} type="number" placeholder="Year" class="border p-2 rounded" />
			<button
				class="col-span-2 bg-blue-600 hover:bg-blue-700 text-white px-4 py-2 rounded"
				on:click={() => create_item(toInsert)}
			>
				Add Book
			</button>
		</div>
	</div>

	<!-- Fetch Button -->
	<div class="mb-4">
		<button
			class="bg-gray-700 hover:bg-gray-800 text-white px-4 py-2 rounded"
			on:click={getBooks}
		>
			📦 Fetch Books
		</button>
	</div>

	<!-- Books Table -->
	{#if fetchBooks.length > 0}
		<table class="w-full border-collapse">
			<thead>
				<tr class="bg-gray-100">
					<th class="p-2 border">ID</th>
					<th class="p-2 border">Title</th>
					<th class="p-2 border">Author</th>
					<th class="p-2 border">Genre</th>
					<th class="p-2 border">YearPublished</th>
					<th class="p-2 border">Actions</th>
				</tr>
			</thead>
			<tbody>
				{#each fetchBooks as book (book.identifier)}
					<tr>
						<td class="p-2 border">{book.identifier}</td>
						<td class="p-2 border">{book.title}</td>
						<td class="p-2 border">{book.author}</td>
						<td class="p-2 border">{book.genre}</td>
						<td class="p-2 border">{book.YearPublished}</td>
						<td class="p-2 border space-x-2">
							<button
								class="bg-yellow-500 text-white px-2 py-1 rounded"
								on:click={() => updateBook(book)}
							>
								Update
							</button>
							<button
								class="bg-red-600 text-white px-2 py-1 rounded"
								on:click={() => deleteBook(book)}
							>
								Delete
							</button>
						</td>
					</tr>
				{/each}
			</tbody>
		</table>
	{/if}
</main>