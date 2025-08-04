export {};

declare global {
	interface SaucerExposed {
		create_book: (book: string) => Promise<boolean>;
		update_book: (book: string) => Promise<boolean>;
		delete_book: (book: string) => Promise<boolean>;
		fetchItems: () => Promise<string>;
	}

	interface Saucer {
		exposed: SaucerExposed;
	}

	interface Window {
		saucer: Saucer;
	}
}
