(ns pso.core
  (:use clojure.core func.core
        [clojure.pprint :only [pprint]])
  (:require [clojure.core.matrix :as mat]
            [clojure.core.matrix.operators :as op]
            ;; [clojure.core.async :refer [chan buffer go go-loop timeout >! >!! <! <!! close! alt!]]
            )
  (:import [mikera.matrixx Matrix]
           [mikera.vectorz Vector]))

(set! *warn-on-reflection* true)

(mat/set-current-implementation :vectorz)

(defn seed-agents
  "Seeding agents' initial positions, based on range and dimension number"
  [agent-count search-ranges]
  (let [[dim _] (mat/shape search-ranges)
        m       (Matrix/create dim agent-count)]
    ;; (print m)
    (loop [r 0]
      (when (< r dim)
        (let [start (mat/mget search-ranges r 0)
              end   (mat/mget search-ranges r 1)
              range (- end start)]
          (loop [c 0]
            (when (< c agent-count)
              (.set m r c (+ start (* (Math/random) range)))
              (recur (unchecked-inc c)))))
        (recur (unchecked-inc r))))
    m))

(defn update-pos
  "Update swarm agents' position"
  [v]
  (let [[_ agent-count] (mat/shape v)
        r_a1 (Matrix/createRandom 1 agent-count)
        r_a2 (Matrix/createRandom 1 agent-count)]
    ))

(defn search
  "Particle swarm search:
  update scheme:
      x(k + 1) = x(k) + v(k)
      v(k + 1) = w.v(k) + r(0, a_1).(x_localbest(k) - x(k)) + r(0, a_2).(x_globalbest(k) - x(k))
  w: should be between [0.9, 1.2]
  search-range: a n by 2 matrix, row number indicates the dimension number
                each row indicates the search range for that dimension
  "
  [func & {:keys [agent-count  search-range debug]
           :or   {agent-count  (long 100)
                  search-range (mat/matrix :vectorz [[-10 10]])
                  debug        false}}]

  (let [[row col] (mat/shape search-range)
        init-pos  (seed-agents agent-count search-ranges)
        cores     (.availableProcessors (Runtime/getRuntime))]
    (if debug
      (pprint {:count agent-count
               :range search-range
               :dim   row
               :col   col}))
    )

  )
