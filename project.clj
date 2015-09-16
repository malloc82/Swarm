(defproject swarm "0.0.1"
  :description "Particle Swarm Optimization & Superiorization"
  ;; :url "http://example.com/FIXME"
  ;; :license {:name "Eclipse Public License"
  ;;           :url "http://www.eclipse.org/legal/epl-v10.html"}
  :source-paths ["src" "src/clojure"]
  :dependencies [[org.clojure/clojure "1.7.0"]
                 [net.mikera/core.matrix "0.40.0"]
                 [net.mikera/vectorz     "0.50.0"]
                 [net.mikera/vectorz-clj "0.34.0"]
                 [clatrix "0.5.0"]
                 [incanter/incanter-charts "1.5.6"]
                 [org.clojure/core.async "0.1.346.0-17112a-alpha"]]
  ;; :jvm-opts ^:replace ["-server" "-XX:+UseCompressedOops" "-XX:+AggressiveOpts"
  ;;                      "-XX:+UnlockCommercialFeatures"
  ;;                      "-XX:+FlightRecorder"]
  :jvm-opts ^:replace []
)
