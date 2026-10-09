import React, { useState } from 'react';
import { Ghost, User, Flame, ArrowRight, Eye, RefreshCw } from 'lucide-react';

const INITIAL_ROOMS = [
  { id: 1, name: 'Entrance', danger: 0, hasPlayer: true, hasGhost: false, hasTrap: false },
  { id: 2, name: 'Grand Hall', danger: 10, hasPlayer: false, hasGhost: false, hasTrap: false },
  { id: 3, name: 'Dining Room', danger: 15, hasPlayer: false, hasGhost: true, hasTrap: false },
  { id: 4, name: 'Library', danger: 25, hasPlayer: false, hasGhost: false, hasTrap: false },
  { id: 5, name: 'Secret Passage', danger: 35, hasPlayer: false, hasGhost: false, hasTrap: false },
  { id: 6, name: 'Haunted Gallery', danger: 50, hasPlayer: false, hasGhost: false, hasTrap: false },
  { id: 7, name: 'Attic', danger: 70, hasPlayer: false, hasGhost: false, hasTrap: false },
  { id: 8, name: 'Exit', danger: 0, hasPlayer: false, hasGhost: false, hasTrap: false },
];

export default function App() {
  const [rooms, setRooms] = useState(INITIAL_ROOMS);
  const [trapsLeft, setTrapsLeft] = useState(2);
  const [scanMessage, setScanMessage] = useState('');
  const [gameState, setGameState] = useState('PLAYING');

  const playerIdx = rooms.findIndex((r) => r.hasPlayer);
  const ghostIdx = rooms.findIndex((r) => r.hasGhost);

  const moveGhost = (currentRooms, currentPIdx) => {
    let gIdx = currentRooms.findIndex((r) => r.hasGhost);
    if (gIdx === -1) return currentRooms;

    if (Math.random() < 0.4) {
      setScanMessage('👻 The ghost haunted its room and stayed still!');
      return currentRooms;
    }

    const nextGIdx = gIdx + 1;
    let newRooms = currentRooms.map((r, i) => ({
      ...r,
      hasGhost: i === nextGIdx,
    }));

    if (newRooms[nextGIdx]?.hasTrap) {
      setGameState('WON');
      setScanMessage('💥 BOOM! The ghost stepped into your trap!');
      return newRooms;
    }

    if (newRooms[nextGIdx]?.name === 'Exit') {
      setGameState('LOST');
      setScanMessage('😱 The ghost reached the Exit and escaped!');
      return newRooms;
    }

    if (nextGIdx === currentPIdx) {
      setGameState('WON');
      setScanMessage('💥 You caught the ghost!');
      return newRooms;
    }

    return newRooms;
  };

  const handleMovePlayer = () => {
    if (gameState !== 'PLAYING' || playerIdx >= rooms.length - 1) return;

    const nextPIdx = playerIdx + 1;
    let updatedRooms = rooms.map((r, i) => ({
      ...r,
      hasPlayer: i === nextPIdx,
    }));

    if (nextPIdx === ghostIdx) {
      setRooms(updatedRooms);
      setGameState('WON');
      setScanMessage('💥 You walked right into the ghost! You caught it!');
      return;
    }

    updatedRooms = moveGhost(updatedRooms, nextPIdx);
    setRooms(updatedRooms);
  };

  const handleScan = () => {
    if (gameState !== 'PLAYING') return;
    const distance = ghostIdx - playerIdx;
    if (distance > 0) {
      setScanMessage(`🔦 SCANNER: Ghost detected ${distance} room(s) ahead!`);
    } else if (distance === 0) {
      setScanMessage('⚠️ SCANNER: Ghost is in your room!');
    } else {
      setScanMessage('❓ SCANNER: Ghost is behind you or not detected ahead.');
    }
  };

  const handleSetTrap = () => {
    if (gameState !== 'PLAYING' || trapsLeft <= 0) return;
    const targetIdx = playerIdx + 1;

    if (targetIdx >= rooms.length) return;
    if (rooms[targetIdx].hasTrap) {
      setScanMessage('⚠️ That room already has a trap!');
      return;
    }

    let updatedRooms = rooms.map((r, i) =>
      i === targetIdx ? { ...r, hasTrap: true } : r
    );

    setTrapsLeft((prev) => prev - 1);
    setScanMessage(`🪤 Trap placed ahead in ${rooms[targetIdx].name}!`);

    updatedRooms = moveGhost(updatedRooms, playerIdx);
    setRooms(updatedRooms);
  };

  const resetGame = () => {
    setRooms(INITIAL_ROOMS);
    setTrapsLeft(2);
    setScanMessage('');
    setGameState('PLAYING');
  };

  return (
    <div style={{ minHeight: '100vh', backgroundColor: '#090d16', color: '#fff', padding: '2rem', display: 'flex', flexDirection: 'column', alignItems: 'center', fontFamily: 'sans-serif' }}>
      <h1 style={{ fontSize: '2rem', fontWeight: 'bold', color: '#c084fc', marginBottom: '2rem' }}>
        👻 GHOST HUNTER: LINKED LIST GUI
      </h1>

      {/* Linked List Nodes */}
      <div style={{ display: 'flex', alignItems: 'center', gap: '1rem', overflowX: 'auto', maxWidth: '100%', padding: '1.5rem', backgroundColor: '#111827', borderRadius: '1rem', border: '1px solid #1f2937', marginBottom: '2rem' }}>
        {rooms.map((room, idx) => (
          <React.Fragment key={room.id}>
            <div style={{
              minWidth: '130px',
              padding: '1rem',
              borderRadius: '0.75rem',
              border: room.hasPlayer ? '2px solid #10b981' : room.hasGhost ? '2px solid #a855f7' : room.hasTrap ? '2px solid #f59e0b' : '2px solid #374151',
              backgroundColor: room.hasPlayer ? 'rgba(6, 78, 59, 0.4)' : room.hasGhost ? 'rgba(88, 28, 135, 0.4)' : '#1f2937',
              display: 'flex',
              flexDirection: 'column',
              alignItems: 'center',
              justifyContent: 'space-between',
              height: '120px'
            }}>
              <span style={{ fontWeight: 'bold', fontSize: '0.9rem', textAlign: 'center' }}>{room.name}</span>
              <div style={{ display: 'flex', gap: '0.5rem', margin: '0.5rem 0' }}>
                {room.hasPlayer && <User color="#34d399" size={24} />}
                {room.hasGhost && <Ghost color="#c084fc" size={24} />}
                {room.hasTrap && <Flame color="#fbbf24" size={24} />}
              </div>
              <span style={{ fontSize: '0.75rem', color: '#9ca3af' }}>Danger: {room.danger}</span>
            </div>
            {idx < rooms.length - 1 && <ArrowRight color="#4b5563" size={20} />}
          </React.Fragment>
        ))}
      </div>

      {/* Status Output */}
      {scanMessage && (
        <div style={{ backgroundColor: '#111827', border: '1px solid #374151', color: '#d8b4fe', padding: '0.75rem 1.5rem', borderRadius: '0.75rem', marginBottom: '1.5rem', textAlign: 'center' }}>
          {scanMessage}
        </div>
      )}

      {/* Game State Messages */}
      {gameState === 'WON' && (
        <div style={{ backgroundColor: '#064e3b', color: '#a7f3d0', padding: '1rem 2rem', borderRadius: '1rem', marginBottom: '1.5rem', fontSize: '1.25rem', fontWeight: 'bold' }}>
          🏆 YOU CAPTURED THE GHOST! YOU WIN!
        </div>
      )}
      {gameState === 'LOST' && (
        <div style={{ backgroundColor: '#881337', color: '#fecdd3', padding: '1rem 2rem', borderRadius: '1rem', marginBottom: '1.5rem', fontSize: '1.25rem', fontWeight: 'bold' }}>
          😱 THE GHOST ESCAPED! GAME OVER!
        </div>
      )}

      {/* Controls */}
      <div style={{ backgroundColor: '#111827', padding: '1.5rem', borderRadius: '1rem', border: '1px solid #1f2937', width: '100%', maxWidth: '500px' }}>
        <div style={{ display: 'flex', justifyContent: 'space-between', marginBottom: '1rem', color: '#d1d5db', fontWeight: '600' }}>
          <span>📍 Location: <strong style={{ color: '#34d399' }}>{rooms[playerIdx]?.name}</strong></span>
          <span>🪤 Traps Left: <strong style={{ color: '#fbbf24' }}>{trapsLeft}</strong></span>
        </div>

        <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: '0.75rem' }}>
          <button onClick={handleMovePlayer} disabled={gameState !== 'PLAYING'} style={{ backgroundColor: '#059669', color: '#fff', border: 'none', padding: '0.75rem', borderRadius: '0.5rem', fontWeight: 'bold', cursor: 'pointer' }}>
            Move
          </button>
          <button onClick={handleScan} disabled={gameState !== 'PLAYING'} style={{ backgroundColor: '#0891b2', color: '#fff', border: 'none', padding: '0.75rem', borderRadius: '0.5rem', fontWeight: 'bold', cursor: 'pointer' }}>
            Scan
          </button>
          <button onClick={handleSetTrap} disabled={gameState !== 'PLAYING' || trapsLeft <= 0} style={{ backgroundColor: '#d97706', color: '#fff', border: 'none', padding: '0.75rem', borderRadius: '0.5rem', fontWeight: 'bold', cursor: 'pointer' }}>
            Trap Ahead
          </button>
        </div>

        {gameState !== 'PLAYING' && (
          <button onClick={resetGame} style={{ marginTop: '1rem', backgroundColor: '#7c3aed', color: '#fff', border: 'none', padding: '0.75rem', borderRadius: '0.5rem', fontWeight: 'bold', width: '100%', cursor: 'pointer' }}>
            Play Again
          </button>
        )}
      </div>
    </div>
  );
}