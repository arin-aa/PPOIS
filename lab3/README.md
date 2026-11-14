# Лабораторная работа №3

## Предметная область

Приложение музыкального плеера: каталог, воспроизведение, плейлисты, поиск, рекомендации, тексты песен и теги, пользователи и подписки, социальные функции, синхронизация и офлайн-режим, настройки.

Формат строки: Класс | число полей | число методов | связанные классы.

| Класс | Поля | Методы | Ассоциации (связанные классы) |
|-------|------|--------|-------------------------------|
| Account | 2 | 1 | — |
| Album | 4 | 1 | MediaLibrary |
| AppSettings | 5 | 1 | — |
| AppTheme | 3 | 1 | — |
| Artist | 4 | 2 | MediaLibrary |
| Artwork | 1 | 1 | — |
| AudioEngine | 4 | 4 | AudioFile |
| AudioFile | 4 | 2 | — |
| AuthenticationService | 2 | 2 | User |
| CloudStorage | 3 | 2 | — |
| Comment | 4 | 1 | — |
| ContentCatalog | 2 | 2 | MediaLibrary |
| CrossfadeSettings | 1 | 1 | — |
| Device | 5 | 2 | — |
| DownloadManager | 3 | 2 | — |
| Equalizer | 1 | 2 | — |
| FavoritesCollection | 3 | 2 | — |
| Follow | 3 | 1 | — |
| Genre | 2 | 1 | — |
| ListeningActivity | 3 | 1 | Track |
| Lyrics | 3 | 1 | TimedLyric |
| MediaLibrary | 4 | 6 | Album, Artist, Genre, Track |
| MetadataProvider | 1 | 1 | — |
| NotificationSettings | 2 | 1 | — |
| OfflineCache | 5 | 4 | — |
| PlaybackHistory | 2 | 2 | PlaybackSession |
| PlaybackSession | 3 | 2 | Track |
| PlaybackState | 4 | 2 | Track |
| Player | 4 | 8 | AudioEngine, PlaybackHistory, PlaybackState, Queue, Track |
| Playlist | 5 | 3 | PlaylistItem, Track |
| PlaylistItem | 2 | 1 | Track |
| PrivacySettings | 2 | 1 | — |
| Queue | 3 | 3 | Track |
| RadioStation | 2 | 2 | — |
| RecommendationService | 2 | 2 | MediaLibrary, PlaybackHistory |
| SearchQuery | 2 | 3 | — |
| SearchResult | 3 | 2 | Album, Artist, Track |
| SearchService | 1 | 2 | ContentCatalog, SearchQuery |
| SharedPlaylist | 3 | 2 | Playlist |
| SleepTimer | 1 | 1 | — |
| SmartPlaylist | 2 | 3 | MediaLibrary, Track |
| Subscription | 3 | 2 | — |
| SyncConflict | 3 | 1 | — |
| SyncService | 1 | 1 | CloudStorage |
| TagEditor | 1 | 3 | — |
| TimedLyric | 2 | 1 | — |
| Track | 7 | 4 | AudioFile |
| User | 4 | 2 | Subscription |
| UserFeed | 2 | 1 | Follow, ListeningActivity |
| UserProfile | 3 | 1 | — |

## Исключения (12)

- MusicPlayerException
- AuthenticationException
- UserNotFoundException
- InvalidPasswordException
- SubscriptionExpiredException
- TrackNotFoundException
- PlaybackException
- AudioEngineException
- PlaylistException
- SyncException
- DownloadException
- MetadataException

Формат строки: Исключение | число полей | число методов | базовый класс.

| Исключение | Поля | Методы | Базовый класс |
|------------|------|--------|---------------|
| MusicPlayerException | 0 | 0 | std::runtime_error |
| AuthenticationException | 1 | 1 | MusicPlayerException |
| UserNotFoundException | 1 | 1 | MusicPlayerException |
| InvalidPasswordException | 1 | 1 | MusicPlayerException |
| SubscriptionExpiredException | 1 | 1 | MusicPlayerException |
| TrackNotFoundException | 1 | 1 | MusicPlayerException |
| PlaybackException | 1 | 1 | MusicPlayerException |
| AudioEngineException | 1 | 1 | MusicPlayerException |
| PlaylistException | 1 | 1 | MusicPlayerException |
| SyncException | 1 | 1 | MusicPlayerException |
| DownloadException | 1 | 1 | MusicPlayerException |
| MetadataException | 1 | 1 | MusicPlayerException |

## Итоговая статистика

| Показатель | Значение |
|------------|----------|
| Классы | 50 |
| Поля | 152 |
| Поведения | 111 |
| Ассоциации | 38 |
| Исключения | 12 |